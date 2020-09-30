#include "SemiMachine.h"
#include "BitMagic.h"

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
using namespace bitmagic;

// LR : 用来处理大整数
// R12: 用来装盛全局变量地址

#define ARM_V8
#define REGALLOC

// #define ROUGH_VERSION
namespace semimachine {

// Provide operation for semimachine blocks

void SemiMachineBlock::deleteBlock() {
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

void SemiMachineBlock::deleteInstruction(SemiMachineInstruction *inst) {
  if (head == nullptr || inst == nullptr) return;
  auto pred = getHead();
  if (pred == inst) {
    setHead(pred->getNext());
    delete pred;
  }
  auto current = pred->getNext();
  while (current != inst && current != nullptr) {
    pred = current;
    current = current->getNext();
  }
  if (current == inst) {
    pred->setNext(current->getNext());
    delete current;
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

void SemiMachineBlock::DeleteUselessInstruction() {
  auto inst = getHead();
  while (inst != nullptr) {
    std::string opcode = inst->getOp();
    auto dst = inst->getDst();
    auto op1 = inst->getOp1();
    auto op2 = inst->getOp2();
    if (opcode == "mov") {
      if (dst->getType() == SemiMachineOprand::Register && op1->getType() == dst->getType()) {
        if (dst->getTag() == op1->getTag()) {
          auto temp = inst->getNext();
          deleteInstruction(inst);
          if (temp == nullptr) break;
          inst = temp;
          continue;
        }
      }
    }

    else if (opcode == "add" || opcode == "sub") {
      if (dst->getType() == SemiMachineOprand::Register && op1->getType() == dst->getType() 
          && op2->getType() == SemiMachineOprand::Constant) {
        if (op2->getValue() == 0) {
          if (dst->getTag() == op1->getTag()) {
            auto temp = inst->getNext();
            deleteInstruction(inst);
            if (temp == nullptr) break;
            inst = temp;
            continue;
          } 
          else {
            inst->setopcode("mov");
            inst->setoprand2(nullptr);
          }
        }
      }
    }

    else if (opcode == "mul" || opcode == "sdiv") {
      if (dst->getType() == SemiMachineOprand::Register && op1->getType() == dst->getType() 
          && op2->getType() == SemiMachineOprand::Constant) {
        if (op2->getValue() == 1) {
          if (dst->getTag() == op1->getTag()) {
            auto temp = inst->getNext();
            deleteInstruction(inst);
            if (temp == nullptr) break;
            inst = temp;
            continue;
          }
          else {
            inst->setopcode("mov");
            inst->setoprand2(nullptr);
          }
        }

      }
    }

    inst = inst->getNext();
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

#ifdef REGALLOC
bool HasRegAllocated(Value *item) {
  if (isa<GlobalVariable>(item) || isa<ReturnInst>(item) || isa<BranchInst>(item) || isa<StoreInst>(item) ||
      isa<AllocaInst>(item) || isa<ICmpInst>(item) || isa<Constant>(item)) {
    return false;
  } else {
    if (auto CI = cast<CallInst>(item)) {
      auto FTy = CI->getFunctionType();
      if (FTy->getReturnType()->isVoidTy())
        return false;
      else
        return true;
    } else {
      if (auto PhiO = cast<PHINode>(item))
        if (PhiO->isPHISpilled)
          return false;
      return true;
    }
  }
}
#endif

#ifdef REGALLOC
SemiMachineOprand *ProcessSpillOut(int offset, SemiMachineBlock &semiblock) {
  int max_num = 65535;
  if (offset > 127 || offset < -128) {
    // auto inst = "\tmovw\tlr, #" + std::to_string(offset & max_num);
    // * inst = movw lr, #(offset & maxnum)
    auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
    auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, offset & max_num);
    auto inst1 = new SemiMachineInstruction("movw", inst1_dst, inst1_oprand1);
    semiblock.addInstruction(inst1);
    int high_num = (unsigned int)offset >> 16;
    if (high_num != 0) {
      // auto inst1 = "\tmovt\tlr, #" + std::to_string(high_num);
      // * movt lr, #high_num
      auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, //
                                             "lr");
      auto inst2_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, high_num);
      auto inst2 = new SemiMachineInstruction("movt", inst2_dst, inst2_oprand1);
      semiblock.addInstruction(inst2);
    }
    SemiMachineOprand *result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
    return result;
  } else {
    // std::cout << "returning: " << offset << "\n";
    SemiMachineOprand *result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, offset);
    // std::cout << "before return val = " << result->getValue() << std::endl;
    // std::cout << "before return type = " << result->getPrintableString() << std::endl;
    return result;
  }
}

SemiMachineOprand *ProcessSpillOut(int offset, int ri, SemiMachineBlock &semiblock) {
  int max_num = 65535;
  if (offset > 127 || offset < -128) {
    // auto inst = "\tmovw\tr" + std::to_string(ri) + ", #" + std::to_string(offset & max_num);
    // * movw ri, #(offset & max_num)
    std::string register_name = "r" + std::to_string(ri);
    auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
    auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, offset & max_num);
    // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
    auto inst1 = new SemiMachineInstruction("movw", inst1_dst, inst1_oprand1);
    semiblock.addInstruction(inst1);
    int high_num = (unsigned int)offset >> 16;
    if (high_num != 0) {
      // auto inst1 = "\tmovt\tr" + std::to_string(ri) + ", #" + std::to_string(high_num);
      // * movt ri, #highnum
      auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, //
                                             register_name);
      auto inst2_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, high_num);
      // auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Mov_);
      auto inst2 = new SemiMachineInstruction("movt", inst2_dst, inst2_oprand1);
      semiblock.addInstruction(inst2);
    }
    SemiMachineOprand *result =
        new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
    return result;
  } else {
    SemiMachineOprand *result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, offset);
    return result;
  }
}

#else
std::string ProcessSpillOut(int offset, int ri, SemiMachineBlock &semiblock) {
  int max_num = 65535;
  if (offset > 127 || offset < -128) {
    auto inst = "\tmovw\tr" + std::to_string(ri) + ", #" + std::to_string(offset & max_num);
    auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
    semiblock.addInstruction(I);
    int high_num = (unsigned int)offset >> 16;
    if (high_num != 0) {
      auto inst1 = "\tmovt\tr" + std::to_string(ri) + ", #" + std::to_string(high_num);
      auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Mov_);
      semiblock.addInstruction(I1);
    }
    return "r" + std::to_string(ri);
  } else {
    return "#" + std::to_string(offset);
  }
}
#endif

#ifdef REGALLOC
SemiMachineOprand *GetOperand(Value *Operand, SemiMachineBlock &semiblock) {
  if (auto GV = cast<GlobalVariable>(Operand)) {
    // std::cout << "Operand is an " << GV->getType()->getTypeName() << std::endl;
    auto offset = current_used_global_variable.size();
    if (!current_used_global_variable.count(GV)) {
      current_used_global_variable[GV] = offset * 4;
      used_gv_in_order.push_back(GV);
    }
    assert(current_used_global_variable.count(GV) && "This GV is not in current_used_global_variable");

    offset = current_used_global_variable[GV];

    // auto inst = "\tadrl\tr12, " + TheFunction->getGVBBName() + "+" + std::to_string(offset);
    // * adrl r12, functionname + offset
    std::string register12 = "r12";
    std::string func_addr = TheFunction->getGVBBName() + "+" + std::to_string(offset);
    auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register12);
    auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, func_addr);
    // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Ld_);
    auto inst1 = new SemiMachineInstruction("adrl", inst1_dst, inst1_oprand1);

    // auto inst1 = "\tldr\tr12, [r12]";
    // * ldr r12, [r12]
    auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register12);
    auto inst2_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "[" + register12 + "]");
    // auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Ld_);
    auto inst2 = new SemiMachineInstruction("ldr", inst2_dst, inst2_oprand1);
    semiblock.addInstruction(inst1);
    semiblock.addInstruction(inst2);

    auto result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register12);
    return result;
  }

  if (auto AI = cast<AllocaInst>(Operand)) {
    auto offset = temp_value[AI];
    offset = current_func_alloc_size - offset;

    // auto inst = "\tadd\tr12, sp, " + ProcessSpillOut(offset, semiblock);
    // * add r12, sp, ProcessSpillOut(offset, semiblock)
    std::string register12 = "r12";
    std::string registersp = "sp";

    auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register12);
    auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, registersp);
    auto inst1_oprand2 = ProcessSpillOut(offset, semiblock);
    // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Add_);
    auto inst1 = new SemiMachineInstruction("add", inst1_dst, inst1_oprand1, inst1_oprand2);
    semiblock.addInstruction(inst1);

    auto result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register12);
    return result;
  }
  if (auto IO = cast<Instruction>(Operand)) {
    if (!HasRegAllocated(IO)) {
      std::cout << IO->getOpcodeName() << std::endl;
    }
    // assert(HasRegAllocated(IO) && "Operand is Void Type");
    auto result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, IO->getReg());
    return result;
  }

  if (auto CO = cast<ConstantInt>(Operand)) {
    auto imm = CO->getValue();
    auto ret_result = ProcessSpillOut(imm, semiblock);
    // std::cout << imm << std::endl;
    if (ret_result->getType() == SemiMachineOprand::SemiMachineOprandType::Constant) {
      std::string inst;
      // inst = "\tmov\tlr, " + ret_result;
      // * mov lr, ret_result
      auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
      // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
      auto inst1 = new SemiMachineInstruction("mov", inst1_dst, ret_result);
      // std::cout << "mov val = " << ret_result->getPrintableString() << std::endl;
      semiblock.addInstruction(inst1);
    }
    auto result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
    return result;
  }

  if (auto ArgumentO = cast<Argument>(Operand)) {
    if (ArgumentO->getArgNo() < 4) {
      auto result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, ArgumentO->getReg());
      return result;
    } else {
      assert(!ArgumentO->getType()->isVoidTy() && "Operand is Void Type");
      assert(temp_value.count(ArgumentO) && "Operand is not defined");

      auto offset = temp_value[ArgumentO];
      offset = current_func_alloc_size - offset;
      // auto inst = "\tldr\tlr, [sp, " + ProcessSpillOut(offset, semiblock) + "]";
      // * ldr lr, [sp + offset]
      auto offset_spillout = ProcessSpillOut(offset, semiblock);
      auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
      auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other,
                                                 "[sp, " + offset_spillout->getPrintableString() + "]");
      // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Ld_);
      auto inst1 = new SemiMachineInstruction("ldr", inst1_dst, inst1_oprand1);
      semiblock.addInstruction(inst1);

      auto result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
      return result;
    }
  }
  auto result = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "<badref>");
  return result;
}

SemiMachineBlock GetOperand(Value *Operand, int ri) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  if (auto GV = cast<GlobalVariable>(Operand)) {
    // std::cout << "Operand is an " << GV->getType()->getTypeName() << std::endl;
    auto offset = current_used_global_variable.size();
    if (!current_used_global_variable.count(GV)) {
      current_used_global_variable[GV] = offset * 4;
      used_gv_in_order.push_back(GV);
    }
    assert(current_used_global_variable.count(GV) && "This GV is not in current_used_global_variable");
    offset = current_used_global_variable[GV];
    // auto inst = "\tadrl\tr" + std::to_string(ri) + ", " + TheFunction->getGVBBName() + "+" + std::to_string(offset);
    // * adrl ri, func_name + offset
    std::string register_name = "r" + std::to_string(ri);
    std::string func_addr = TheFunction->getGVBBName() + "+" + std::to_string(offset);
    auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
    auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, func_addr);
    // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Ld_);
    auto inst1 = new SemiMachineInstruction("adrl", inst1_dst, inst1_oprand1);

    // auto inst1 = "\tldr\tr" + std::to_string(ri) + ", [r" + std::to_string(ri) + "]";
    // * ldr ri, [ri]
    auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
    auto inst2_oprand1 =
        new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "[" + register_name + "]");
    // auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Ld_);
    auto inst2 = new SemiMachineInstruction("ldr", inst2_dst, inst2_oprand1);
    semiblock.addInstruction(inst1);
    semiblock.addInstruction(inst2);

    return semiblock;
  }

  if (auto AI = cast<AllocaInst>(Operand)) {
    auto offset = temp_value[AI];
    offset = current_func_alloc_size - offset;
    // auto inst = "\tadd\tr" + std::to_string(ri) + ", sp, " + ProcessSpillOut(offset, semiblock);
    // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Ld_);

    // * add ri, sp, ProcessSpillOut(offset, semiblock)
    std::string register_name = "r" + std::to_string(ri);
    std::string registersp = "sp";

    auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
    auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, registersp);
    auto inst1_oprand2 = ProcessSpillOut(offset, semiblock);
    // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Add_);
    auto inst1 = new SemiMachineInstruction("add", inst1_dst, inst1_oprand1, inst1_oprand2);
    semiblock.addInstruction(inst1);

    return semiblock;
  }

  if (auto IO = cast<Instruction>(Operand)) {
    // if(!HasRegAllocated(IO)){
    //   std::cout << " >> IO: " << IO->FOrder << " " << IO->getOpcodeName();
    //   std::cout << " at Function: " << IO->getFunction()->getName() << std::endl;
    // }
    assert(HasRegAllocated(IO) && "Operand is Void Type");
    if (IO->getColor() != ri) {
      // auto inst = "\tmov\tr" + std::to_string(ri) + ", " + IO->getReg();
      // * mov ri, IO->getReg()
      std::string register_name = "r" + std::to_string(ri);
      std::string register_fetch = IO->getReg();
      auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
      auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_fetch);
      // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
      auto inst1 = new SemiMachineInstruction("mov", inst1_dst, inst1_oprand1);
      semiblock.addInstruction(inst1);
    }
    return semiblock;
  }

  if (auto CO = cast<ConstantInt>(Operand)) {
    auto imm = CO->getValue();
    // std::string inst;
    // inst = "\tmov\tr" + std::to_string(ri) + ", " + ProcessSpillOut(imm, ri, semiblock);
    // * mov ri, imm
    std::string register_name = "r" + std::to_string(ri);
    auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
    auto inst1_oprand1 = ProcessSpillOut(imm, ri, semiblock);
    // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
    auto inst1 = new SemiMachineInstruction("mov", inst1_dst, inst1_oprand1);
    semiblock.addInstruction(inst1);
    return semiblock;
  }

  if (auto ArgumentO = cast<Argument>(Operand)) {
    if (ArgumentO->getArgNo() < 4) {
      // auto inst = "\tmov\tr" + std::to_string(ri) + ", " + ArgumentO->getReg();
      // * mov ri, ArgumentO
      std::string register_name = "r" + std::to_string(ri);
      std::string arg_reg = ArgumentO->getReg();
      auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
      auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, arg_reg);
      // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
      auto inst1 = new SemiMachineInstruction("mov", inst1_dst, inst1_oprand1);
      semiblock.addInstruction(inst1);
      return semiblock;
    } else {
      assert(!ArgumentO->getType()->isVoidTy() && "Operand is Void Type");
      assert(temp_value.count(ArgumentO) && "Operand is not defined");

      auto offset = temp_value[ArgumentO];
      offset = current_func_alloc_size - offset;

      // auto inst = "\tldr\tr" + std::to_string(ri) + ", [sp, " + ProcessSpillOut(offset, semiblock) + "]";
      // * ldr ri, [sp, offset]
      std::string register_name = "r" + std::to_string(ri);
      auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
      auto offset_spillout = ProcessSpillOut(offset, semiblock);
      auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register,
                                                 "[sp, " + offset_spillout->getPrintableString() + "]");
      // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Ld_);
      auto inst1 = new SemiMachineInstruction("ldr", inst1_dst, inst1_oprand1);
      semiblock.addInstruction(inst1);

      return semiblock;
    }
  }
  // Operand->getType()->print();
  // std::cout << "WRONG：No Such Operand As " << Operand->getType()->getTypeName() << std::endl;
  return semiblock;
}
#else
SemiMachineBlock GetOperand(Value *Operand, int ri) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  if (auto GV = cast<GlobalVariable>(Operand)) {
    // std::cout << "Operand is an " << GV->getType()->getTypeName() << std::endl;
    auto offset = current_used_global_variable.size();
    if (!current_used_global_variable.count(GV)) {
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
  if (auto AI = cast<AllocaInst>(Operand)) {
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
#endif

#ifndef REGALLOC
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
#endif

#ifdef REGALLOC
SemiMachineBlock IRToSemiEntryBB() {
  assert(temp_value.empty() && "At EntryBloack temp_value is not empty");
  assert(TheFunction && "Processed function is nullptr");
  SemiMachineBlock semiblock = SemiMachineBlock();
  // std::cout << "@ After Enter EntryBB" << std::endl;
  int fNext = 0;
  int16_t num_of_most_trans_parameter = 0;
  int slot_num = TheFunction->Arg_size();
  for (auto it = TheFunction->BB_begin(); it != TheFunction->BB_end(); it++) {
    for (auto I = (*it)->begin(); I != (*it)->end(); I++) {
      if (HasRegAllocated(*I)) {
        if ((*I)->getColor() || TheFunction->getFunctionType()->isReturnVoid()) {
          // std::cout << "Save reg " << (*I)->getReg() << " by Instruction " << (*I)->FOrder << (*I)->getOpcodeName()
          // << std::endl;
          used_regs.insert((*I)->getColor());
        }
      }
      if (auto AI = cast<AllocaInst>(*I)) {
        auto allocated_size = cast<ConstantInt>(AI->getArraySize());
        assert(allocated_size && "ArraySize of Alloc Inst is Not Constant Int");
        fNext += allocated_size->getValue() * 4;
        temp_value[*I] = fNext;
        // std::string inst =  "\t@ alloc Instruction %" + std::to_string(slot_num) + " alloc space: ["
        //           + std::to_string(fNext - allocated_size->getValue() * 4) + " , " + std::to_string(fNext) + "]" ;
        // semiblock.addInstruction(new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Nop_));
        slot_num++;
        continue;
      }
      if (auto CI = cast<CallInst>(*I)) {
        auto args_num = CI->getNumOperands() - 1;
        if (args_num > num_of_most_trans_parameter) {
          num_of_most_trans_parameter = args_num;
        }
      }
    }
  }

  num_of_most_trans_parameter = (num_of_most_trans_parameter > 3) ? num_of_most_trans_parameter - 4 : 0;

  current_func_alloc_size = 4 * num_of_most_trans_parameter + fNext;

  std::string colors = "";
  fNext = 0;
  for (auto it = used_regs.begin(); it != used_regs.end(); it++) {
    colors += "r" + std::to_string(*it) + ", ";
    fNext -= 4;
  }
  // std::cout << fNext << std::endl;
  colors += "lr";
  fNext -= 4;
  int call_saved_regs_num = 0;
  if (TheFunction->Arg_size() >= 4) {
    call_saved_regs_num = 4;
  } else {
    if (TheFunction->Arg_size()) {
      call_saved_regs_num = TheFunction->Arg_size();
    } else {
      call_saved_regs_num = 1;
    }
  }
  fNext -= 4 * call_saved_regs_num;

  slot_num = 0;
  for (auto it = TheFunction->Arg_begin(); it != TheFunction->Arg_end(); ++it) {
    if (slot_num >= 4) {
      temp_value[*it] = fNext;
      // auto Ii = new SemiMachineInstruction("\t@ Arg %" + std::to_string(slot_num) + " Alloc = " +
      // std::to_string(fNext), 0, SemiMachineInstruction::Nop_); semiblock.addInstruction(Ii);
      fNext -= 4;
    } else {
      // auto Ii = new SemiMachineInstruction("\t@ Arg %" + std::to_string(slot_num) + " Alloc : r" +
      // std::to_string(slot_num), 0, SemiMachineInstruction::Nop_); semiblock.addInstruction(Ii);
    }
    // used_regs.insert(slot_num);
    slot_num++;
    // if((*it)->getType()->isPointerTy())
  }

  // std::string inst2 = "\tpush\t{" + colors + "}";
  // * push {colors}
  auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "{" + colors + "}");
  // auto I2 = new SemiMachineInstruction(inst2, 0, SemiMachineInstruction::St_);
  auto inst1 = new SemiMachineInstruction("push", inst1_dst);
  // std::cout << colors << std::endl;
  // semiblock.addInstruction(I1);
  semiblock.addInstruction(inst1);

  // std::string inst3 = "\tsub\tsp, sp, " + ProcessSpillOut(current_func_alloc_size, semiblock);
  // sub sp, sp, " + ProcessSpillOut(current_func_alloc_size, semiblock)
  auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "sp");
  // TODO: Consider about which choice is better:
  // Choice1 - use same pointer for same operand
  // Choice2 - use different pointer for same operand
  auto inst2_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "sp");
  auto inst2_oprand2 = ProcessSpillOut(current_func_alloc_size, semiblock);

  // auto I3 = new SemiMachineInstruction(inst3, 0, SemiMachineInstruction::Sub_);
  auto inst2 = new SemiMachineInstruction("sub", inst2_dst, inst2_oprand1, inst2_oprand2);
  semiblock.addInstruction(inst2);
  return semiblock;
}
#else
// Design the entrance block
SemiMachineBlock IRToSemiEntryBB() {
  assert(temp_value.empty() && "At EntryBloack temp_value is not empty");
  assert(TheFunction && "Processed function is nullptr");
  SemiMachineBlock semiblock = SemiMachineBlock();
  // std::cout << "@ After Enter EntryBB" << std::endl;
  int fNext = 0;
  int16_t num_of_most_trans_parameter = 0;
  int slot_num = TheFunction->Arg_size();
  fNext = (slot_num > 3) ? 16 : 4 * slot_num;
  for (auto it = TheFunction->BB_begin(); it != TheFunction->BB_end(); it++) {
    for (auto I = (*it)->begin(); I != (*it)->end(); I++) {
      if (!(*I)->getType()->isVoidTy()) {
        if (auto AI = cast<AllocaInst>(*I)) {
          auto allocated_size = cast<ConstantInt>(AI->getArraySize());
          assert(allocated_size && "ArraySize of Alloc Inst is Not Constant Int");
          fNext += allocated_size->getValue() * 4;
          temp_value[*I] = fNext;
          slot_num++;
        } else {
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

  num_of_most_trans_parameter = (num_of_most_trans_parameter > 3) ? num_of_most_trans_parameter - 4 : 0;

  current_func_alloc_size = 4 * num_of_most_trans_parameter + fNext;
  std::string inst1 =
      "\t@frame_size = " + std::to_string(fNext / 4) + "\n\t@alloc = " + std::to_string(current_func_alloc_size);
  auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Nop_);

  /// save lr unconditionally
  // FIXME:
  // consinder
  // consider callee-save
  std::string inst2 = "\tpush\t{lr}";
  auto I2 = new SemiMachineInstruction(inst2, 0, SemiMachineInstruction::St_);
  fNext = -4;

  // FIXME:
  // Here don't process the 4-th
  slot_num = 0;
  for (auto it = TheFunction->Arg_begin(); it != TheFunction->Arg_end(); ++it) {
    if (slot_num < 4) {
      temp_value[*it] = slot_num * 4 + 4;
    } else {
      temp_value[*it] = fNext;
      fNext -= 4;
    }
    // std::cout << "\t @ Arg %" << slot_num << " Alloc : " << temp_value[*it] << std::endl;
    slot_num++;
    // if((*it)->getType()->isPointerTy())
  }

  semiblock.addInstruction(I1);
  semiblock.addInstruction(I2);

  std::string inst3 = "\tsub\tsp, sp, " + ProcessSpillOut(current_func_alloc_size, 4, semiblock);
  auto I3 = new SemiMachineInstruction(inst3, 0, SemiMachineInstruction::Sub_);
  semiblock.addInstruction(I3);

  // unneccessary operations, don't need store
  slot_num = 0;
  for (auto it = TheFunction->Arg_begin(); it != TheFunction->Arg_end(); ++it) {
    if (slot_num < 4) {
      semiblock += StoreTempValue(*it, slot_num);
      slot_num++;
      continue;
    }
    break;
  }
  return semiblock;
}
#endif

#ifdef REGALLOC
// Design the return basic block
SemiMachineBlock IRToSemiRetBB() {
  assert(TheFunction && "Processed function is nullptr");
  SemiMachineBlock semiblock = SemiMachineBlock();
  std::string ret_bb_name = TheFunction->getRetBBName() + ":";
  // SemiMachineInstruction *ret_bb_label =
  //     new SemiMachineInstruction(ret_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel, 12);
  SemiMachineInstruction *ret_bb_label =
      new SemiMachineInstruction(ret_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel);
  semiblock.addInstruction(ret_bb_label);

  // std::string inst1 = "\tadd\tsp, sp, " + ProcessSpillOut(current_func_alloc_size, semiblock);
  // * add sp, sp, current_func_alloc_size
  auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "sp");
  auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "sp");
  auto inst1_oprand2 = ProcessSpillOut(current_func_alloc_size, semiblock);
  // std::cout << inst1_oprand2->getPrintableString() << std::endl;
  // auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Add_);
  auto inst1 = new SemiMachineInstruction("add", inst1_dst, inst1_oprand1, inst1_oprand2);

  std::string colors = "";
  for (auto it = used_regs.begin(); it != used_regs.end(); it++) {
    colors += "r" + std::to_string(*it) + ", ";
  }

  colors += "lr";
  // std::string inst2 = "\tpop\t{" + colors + "}";
  // auto I2 = new SemiMachineInstruction(inst2, 0, SemiMachineInstruction::Ld_);
  // * pop {colors}
  auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "{" + colors + "}");
  auto inst2 = new SemiMachineInstruction("pop", inst2_dst);
  // std::cout << colors << std::endl;
  // std::string inst3 = "\tbx\tlr";
  // auto I3 = new SemiMachineInstruction(inst3, 0, SemiMachineInstruction::Br_);
  // * bx lr
  auto inst3_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
  auto inst3 = new SemiMachineInstruction("bx", inst3_dst);

  semiblock.addInstruction(inst1);
  semiblock.addInstruction(inst2);
  semiblock.addInstruction(inst3);

  SemiMachineBlock semiblock1 = SemiMachineBlock();
  std::string align_bb_name = TheFunction->getAlignBBName() + ":";
  // SemiMachineInstruction *align_bb_label =
  //     new SemiMachineInstruction(align_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel, 12);
  SemiMachineInstruction *align_bb_label =
      new SemiMachineInstruction(align_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel);
  semiblock1.addInstruction(align_bb_label);

  std::string align_inst = "\t.align\t2";
  auto inst4 = new SemiMachineInstruction(align_inst, SemiMachineInstruction::SemiMachineType::Variable);
  semiblock1.addInstruction(inst4);

  semiblock += semiblock1;

  if (current_used_global_variable.size()) {
    SemiMachineBlock semiblock2 = SemiMachineBlock();
    std::string GV_bb_name = TheFunction->getGVBBName() + ":";
    // SemiMachineInstruction *GV_bb_label =
    //     new SemiMachineInstruction(GV_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel, 12);
    SemiMachineInstruction *GV_bb_label =
        new SemiMachineInstruction(GV_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel);
    semiblock2.addInstruction(GV_bb_label);
    for (auto it : used_gv_in_order) {
      auto word = "\t.word\t" + it->getName();
      auto inst5 = new SemiMachineInstruction(word, SemiMachineInstruction::SemiMachineType::Variable);
      semiblock2.addInstruction(inst5);
    }
    semiblock += semiblock2;
  }
  return semiblock;
}
#else
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
  std::string inst2 = "\tpop\t{lr}";
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
  if (current_used_global_variable.size()) {
    SemiMachineBlock semiblock2 = SemiMachineBlock();
    std::string GV_bb_name = TheFunction->getGVBBName() + ":";
    SemiMachineInstruction *GV_bb_label =
        new SemiMachineInstruction(GV_bb_name, SemiMachineInstruction::SemiMachineType::BBLabel, 12);
    semiblock2.addInstruction(GV_bb_label);
    for (auto it : used_gv_in_order) {
      auto word = "\t.word\t" + it->getName();
      auto I5 = new SemiMachineInstruction(word, 0, SemiMachineInstruction::Nop_);
      semiblock2.addInstruction(I5);
    }
    semiblock += semiblock2;
  }
  return semiblock;
}
#endif

#ifdef REGALLOC
// #ifdef ROUGH_VERSION
// Design translation  for IR:ret
SemiMachineBlock IRToSemiRet(Instruction *instruction_item) {
  // Fetch the ret instruction
  auto val = instruction_item->getNumOperands();
  SemiMachineBlock inst_block = SemiMachineBlock();
  auto RetI = cast<ReturnInst>(instruction_item);

  if (val) {
    inst_block += GetOperand(RetI->getNumOperand(0).get(), 0);
    // if (auto ret_const = cast<ConstantInt>(RetI->getNumOperand(0).get())) {
    //   auto ret_result = ret_const->getValue();
    //   std::string inst;
    //   inst = "\tmov\tr0, " + ProcessSpillOut(ret_result, inst_block);
    //   auto I0 = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
    //   inst_block.addInstruction(I0);
    // } else {
    //   auto op = RetI->getNumOperand(0).get();
    //   if(op->Color != 0){
    //     std::string inst0 = "\tmov\tr0, r" + std::to_string(op->Color);
    //     auto I0 = new SemiMachineInstruction(inst0, 0, SemiMachineInstruction::Mov_);
    //     inst_block.addInstruction(I0);
    //   }
    // }
  }
  // std::string inst = "\tb\t" + TheFunction->getRetBBName();
  // * b Function ret name
  auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, TheFunction->getRetBBName());
  // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Br_);
  auto inst1 = new SemiMachineInstruction("b", inst1_dst);
  inst_block.addInstruction(inst1);
  return inst_block;
}
#else
// #ifdef ROUGH_VERSION
// Design translation  for IR:ret
SemiMachineBlock IRToSemiRet(Instruction *instruction_item) {
  // Fetch the ret instruction
  auto val = instruction_item->getNumOperands();
  SemiMachineBlock inst_block = SemiMachineBlock();
  auto RetI = cast<ReturnInst>(instruction_item);

  if (val) {
    if (auto ret_const = cast<ConstantInt>(RetI->getNumOperand(0).get())) {
      auto ret_result = ret_const->getValue();
      std::string inst;
      inst = "\tmov\tr3, " + ProcessSpillOut(ret_result, 3, inst_block);
      auto I0 = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
      inst_block.addInstruction(I0);
    } else {
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
#endif

#ifdef REGALLOC
SemiMachineBlock IRToSemiBr(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  auto BrI = cast<BranchInst>(instruction_item);
  assert(BrI && "this instruction should be an Br");
  // std::cout << "Enter a branch" << std::endl;
  if (BrI->isConditional()) {
    std::string true_branch_label = BrI->getNumOperand(2)->getName();
    std::string false_branch_label = BrI->getNumOperand(1)->getName();
    // std::cout << "This branch is conditional branch" << std::endl;
    auto pred = BrI->getNumOperand(-3).get();
    if (auto CP = cast<ConstantInt>(pred)) {
      auto cmp_result = CP->getValue();
      // std::cout << "Pred is constant int" << cmp_result << std::endl;
      std::string jump_label = "";
      if (cmp_result) {
        jump_label = true_branch_label;
      } else {
        jump_label = false_branch_label;
      }
      // * b label
      if (!jump_label.empty()) {
        auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, jump_label);
        auto inst1 = new SemiMachineInstruction("b", inst1_dst);
        semiblock.addInstruction(inst1);
      }
    } else {
      auto pred_inst = cast<ICmpInst>(pred);
      assert(pred_inst && "Before CondBr there is some other insts but Icmp insts");
      auto icmp_opcode = pred_inst->getCmpType_codegen();

      // b icmp_opcode
      auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, true_branch_label);
      auto inst1 = new SemiMachineInstruction("b" + icmp_opcode, inst1_dst);
      auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, false_branch_label);
      auto inst2 = new SemiMachineInstruction("b", inst2_dst);

      semiblock.addInstruction(inst1);
      semiblock.addInstruction(inst2);
    }
  } else {
    // std::string inst = "\tb\t" + BrI->getNumOperand(0).get()->getName();
    // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Br_);

    auto inst1_dst =
        new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, BrI->getNumOperand(0).get()->getName());
    auto inst1 = new SemiMachineInstruction("b", inst1_dst);
    semiblock.addInstruction(inst1);
  }

  return semiblock;
}
#else
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
#endif

#ifdef REGALLOC
// FIXME:
// need to be ensured that two constantint cannot exist in the same ICmp inst
SemiMachineBlock IRToSemiIcmp(Instruction *instruction_item) {
  // std::cout << " >>> IRToSemiIcmp" << std::endl;
  // for (int i = 0; i < instruction_item->getNumOperands(); i++) {
  //   std::cout << "        ICmp Op: " << instruction_item->getNumOperand(i).get()->FOrder;
  //   std::cout << " " << instruction_item->getNumOperand(i).get()->getValueID() << std::endl;
  // }

  SemiMachineBlock semiblock = SemiMachineBlock();
  auto IcmpI = cast<ICmpInst>(instruction_item);
  assert(IcmpI && "this instruction should be an Icmp");

  auto s1 = instruction_item->getNumOperand(0).get();
  auto s2 = instruction_item->getNumOperand(1).get();

  SemiMachineOprand *s1_src_reg, *s2_src_reg;
  if (isa<Constant>(s1)) {
    s2_src_reg = GetOperand(s2, semiblock);
    s1_src_reg = GetOperand(s1, semiblock);
  }
  else {
    s1_src_reg = GetOperand(s1, semiblock);
    s2_src_reg = GetOperand(s2, semiblock);
  }

  // std::cout << "----- line 821 -----" << std::endl;
  // auto s1_src_reg = GetOperand(s1, semiblock);
  // if (s1_src_reg->getPrintableString() == "lr") {
  //   // auto new_mov = new SemiMachineInstruction("\tmov\tip, " + s1_src_reg, 0, SemiMachineInstruction::Cmp_);
  //   auto new_mov_dst = new SemiMachineOprand(SemiMachineOprand::Register, "ip");
  //   auto new_mov = new SemiMachineInstruction("mov", new_mov_dst, s1_src_reg);
  //   semiblock.addInstruction(new_mov);
  //   // s1_src_reg = "ip";
  //   s1_src_reg = new SemiMachineOprand(SemiMachineOprand::Register, "ip");
  // }

  // auto s2_src_reg = GetOperand(s2, semiblock);

  // auto I1 = new SemiMachineInstruction("\tcmp\t" + s1_src_reg + ", " + s2_src_reg, 0, SemiMachineInstruction::Cmp_);
  auto inst1 = new SemiMachineInstruction("cmp", s1_src_reg, s2_src_reg);
  // std::cout << "----- line 823 -----" << std::endl;
  semiblock.addInstruction(inst1);
  return semiblock;
}
#else
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
#endif

#ifdef REGALLOC
SemiMachineBlock IRToSemiAdd(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Add && "this instruction should be an ADD");
  auto s1 = instruction_item->getNumOperand(0).get();
  auto s2 = instruction_item->getNumOperand(1).get();
  auto dt = instruction_item->getReg();
  if (isa<Constant>(s1)) {
    auto temp = s1;
    s1 = s2;
    s2 = temp;
  }

  // std::string s1_src_reg = GetOperand(s1, semiblock);
  auto s1_src_reg = GetOperand(s1, semiblock);
  // if (s1_src_reg->getPrintableString() == "lr") {
  //   // auto new_mov = new SemiMachineInstruction("\tmov\tip, " + s1_src_reg, 0, SemiMachineInstruction::Cmp_);
  //   // mov ip, s1_stc_reg
  //   auto new_mov_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
  //   auto new_mov = new SemiMachineInstruction("mov", new_mov_dst, s1_src_reg);
  //   semiblock.addInstruction(new_mov);
  //   // s1_src_reg = "ip";
  //   s1_src_reg = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
  // }
  auto s2_src_reg = GetOperand(s2, semiblock);
  auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  auto inst1 = new SemiMachineInstruction("add", inst1_dst, s1_src_reg, s2_src_reg);
  // auto I3 = new SemiMachineInstruction("\tadd\t" + dt + ", " + s1_src_reg + ", " + s2_src_reg, 0,
  //                                      SemiMachineInstruction::Add_);
  semiblock.addInstruction(inst1);

  return semiblock;
}
#else
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
#endif

#ifdef REGALLOC
SemiMachineBlock IRToSemiSub(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Sub && "this instruction should be a SUB");
  auto s1 = instruction_item->getNumOperand(0).get();
  auto s2 = instruction_item->getNumOperand(1).get();
  auto dt = instruction_item->getReg();

  SemiMachineOprand *s1_src_reg, *s2_src_reg;
  if (isa<Constant>(s1)) {
    s2_src_reg = GetOperand(s2, semiblock);
    s1_src_reg = GetOperand(s1, semiblock);
  }
  else {
    s1_src_reg = GetOperand(s1, semiblock);
    s2_src_reg = GetOperand(s2, semiblock);
  }

  // std::string s1_src_reg = GetOperand(s1, semiblock);
  
  // if (s1_src_reg->getPrintableString() == "lr") {
  //   // auto new_mov = new SemiMachineInstruction("\tmov\tip, " + s1_src_reg, 0, SemiMachineInstruction::Cmp_);
  //   // semiblock.addInstruction(new_mov);
  //   // s1_src_reg = "ip";
  //   auto new_mov_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
  //   auto new_mov = new SemiMachineInstruction("mov", new_mov_dst, s1_src_reg);
  //   semiblock.addInstruction(new_mov);
  //   // s1_src_reg = "ip";
  //   s1_src_reg = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
  // }
  // std::string s2_src_reg = GetOperand(s2, semiblock);
  
  auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  // auto I3 = new SemiMachineInstruction("\tsub\t" + dt + ", " + s1_src_reg + ", " + s2_src_reg, 0,
  //                                      SemiMachineInstruction::Sub_);
  auto inst1 = new SemiMachineInstruction("sub", inst1_dst, s1_src_reg, s2_src_reg);
  semiblock.addInstruction(inst1);

  return semiblock;
}
#else
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
#endif

#ifdef REGALLOC
SemiMachineBlock IRToSemiMul(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Mul && "this instruction should be a MUL");
  auto s1 = instruction_item->getNumOperand(0).get();
  auto s2 = instruction_item->getNumOperand(1).get();
  auto dt = instruction_item->getReg();
  if (isa<Constant>(s1)) {
    auto temp = s1;
    s1 = s2;
    s2 = temp;
  }

  // std::string s1_src_reg = GetOperand(s1, semiblock);
  auto s1_src_reg = GetOperand(s1, semiblock);
  // if (s1_src_reg->getPrintableString() == "lr") {
  //   // auto new_mov = new SemiMachineInstruction("\tmov\tip, " + s1_src_reg, 0, SemiMachineInstruction::Cmp_);
  //   // semiblock.addInstruction(new_mov);
  //   // s1_src_reg = "ip";
  //   auto new_mov_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
  //   auto new_mov = new SemiMachineInstruction("mov", new_mov_dst, s1_src_reg);
  //   semiblock.addInstruction(new_mov);
  //   // s1_src_reg = "ip";
  //   s1_src_reg = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
  // }

  // std::string s2_src_reg = GetOperand(s2, semiblock);
  auto s2_src_reg = GetOperand(s2, semiblock);
  auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  // auto I3 = new SemiMachineInstruction("\tmul\t" + dt + ", " + s1_src_reg + ", " + s2_src_reg, 0,
  //                                      SemiMachineInstruction::Mul_);
  auto inst1 = new SemiMachineInstruction("mul", inst1_dst, s1_src_reg, s2_src_reg);
  semiblock.addInstruction(inst1);
  return semiblock;
  // if (auto CO = cast<ConstantInt>(s2)) {
  //   auto imm = CO->getValue();
  //   if (imm == 0)
  //     return semiblock;
  //   // std::cout << imm << std::endl;
  //   // std::cout << "MUL" << std::endl;
  //   int cost = bitmagic::MultCover(imm);
  //   if (cost > 14) {
  //     auto inst1 = new SemiMachineInstruction("mul", inst1_dst, s1_src_reg, s2_src_reg);
  //     semiblock.addInstruction(inst1);
  //     return semiblock;
  //   } else {
  //     // imm = 25;
  //     bitmagic::MultCover(imm);
  //     auto instseq = bitmagic::GetSolution(imm);
  //     // bitmagic::PrintSolution(imm);
  //     for (auto item : instseq) {
  //       // std::cout << item.first << " " << item.second << std::endl;
  //       switch (item.first) {
  //       case bitmagic::g_opcode::shift: {
  //         if (item.second == 0) {
  //           if (inst1_dst->getPrintableString() == s1_src_reg->getPrintableString()) {
  //             continue;
  //           }
  //           auto institem = new SemiMachineInstruction("mov", inst1_dst, s1_src_reg);
  //           // std::cout << institem->getInstruction() << std::endl;
  //           semiblock.addInstruction(institem);
  //         } else {
  //           auto institem_oprand =
  //               new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, item.second);
  //           auto institem = new SemiMachineInstruction("lsl", inst1_dst, inst1_dst, institem_oprand);
  //           // std::cout << institem->getInstruction() << std::endl;
  //           semiblock.addInstruction(institem);
  //         }
  //       } break;

  //       case bitmagic::g_opcode::shiftadd: {
  //         auto institem = new SemiMachineInstruction("add", inst1_dst, inst1_dst, s1_src_reg);
  //         // std::cout << institem->getInstruction() << std::endl;
  //       } break;

  //       case bitmagic::g_opcode::shiftsub: {
  //         auto institem = new SemiMachineInstruction("sub", inst1_dst, inst1_dst, s1_src_reg);
  //         // std::cout << institem->getInstruction() << std::endl;
  //       } break;

  //       case bitmagic::g_opcode::factoradd: {
  //         auto institem_oprand =
  //             new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other,
  //                                   s1_src_reg->getPrintableString() + ", lsl #" + std::to_string(item.second));
  //         auto institem = new SemiMachineInstruction("add", inst1_dst, inst1_dst, institem_oprand);
  //         // std::cout << institem->getInstruction() << std::endl;
  //       } break;

  //       case bitmagic::g_opcode::factorsub: {
  //         auto institem_oprand =
  //             new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other,
  //                                   s1_src_reg->getPrintableString() + ", lsl #" + std::to_string(item.second));
  //         auto institem = new SemiMachineInstruction("rsub", inst1_dst, s1_src_reg, institem_oprand);
  //         // std::cout << institem->getInstruction() << std::endl;
  //       } break;

  //       default:
  //         break;
  //       }
  //     }
  //     return semiblock;
  //   }
  // } else {
  //   auto inst1 = new SemiMachineInstruction("mul", inst1_dst, s1_src_reg, s2_src_reg);
  //   semiblock.addInstruction(inst1);
  //   return semiblock;
  // }
}
#else
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
#endif

#ifdef ARM_V8
SemiMachineBlock IRToSemiSDiv(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::SDiv && "this instruction should be a SDiv");
  auto s1 = instruction_item->getNumOperand(0).get();
  auto s2 = instruction_item->getNumOperand(1).get();
  auto dt = instruction_item->getReg();

  SemiMachineOprand *s1_src_reg, *s2_src_reg;
  if (isa<Constant>(s1)) {
    s2_src_reg = GetOperand(s2, semiblock);
    s1_src_reg = GetOperand(s1, semiblock);
  }
  else {
    s1_src_reg = GetOperand(s1, semiblock);
    s2_src_reg = GetOperand(s2, semiblock);
  }

  // std::string s1_src_reg = GetOperand(s1, semiblock);
  // auto s1_src_reg = GetOperand(s1, semiblock);
  // if (s1_src_reg->getPrintableString() == "lr") {
  //   // auto new_mov = new SemiMachineInstruction("\tmov\tip, " + s1_src_reg, 0, SemiMachineInstruction::Cmp_);
  //   // semiblock.addInstruction(new_mov);
  //   // s1_src_reg = "ip";
  //   auto new_mov_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
  //   auto new_mov = new SemiMachineInstruction("mov", new_mov_dst, s1_src_reg);
  //   semiblock.addInstruction(new_mov);
  //   // s1_src_reg = "ip";
  //   s1_src_reg = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
  // }

  // auto s2_src_reg = GetOperand(s2, semiblock);
  auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  auto inst1 = new SemiMachineInstruction("sdiv", inst1_dst, s1_src_reg, s2_src_reg);
  semiblock.addInstruction(inst1);

  return semiblock;
  // std::string s2_src_reg = GetOperand(s2, semiblock);
  // auto I3 = new SemiMachineInstruction("\tsdiv\t" + dt + ", " + s1_src_reg + ", " + s2_src_reg, 0,
  //                                      SemiMachineInstruction::Sub_);

  // auto s2_src_reg = GetOperand(s2, semiblock);
  // auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  // auto inst1 = new SemiMachineInstruction("sdiv", inst1_dst, s1_src_reg, s2_src_reg);
  // semiblock.addInstruction(inst1);

  // return semiblock;

  // dt = s1_src_reg / s2_src_reg
  // std::cout << "div" << std::endl;
  // if (auto CO = cast<ConstantInt>(s2)) {
  //   auto imm = CO->getValue();
  //   // imm = 2;
  //   std::cout << imm << std::endl;
  //   if (bitmagic::BitCount(imm) == 1) {
  //     // std::cout << SpecialLog(imm) << std::endl;
  //     auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  //     auto inst1_oprand1 =
  //         new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, s1_src_reg->getPrintableString());
  //     auto inst1_oprand2 =
  //         new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, bitmagic::SpecialLog(imm));
  //     auto inst1 = new SemiMachineInstruction("asr", inst1_dst, inst1_oprand1, inst1_oprand2);
  //     semiblock.addInstruction(inst1);
  //     return semiblock;
  //   }

  //   // std::cout << imm << std::endl;
  //   std::pair<int, int> divfactor = bitmagic::DivCover(imm);
  //   std::cout << divfactor.first << " " << divfactor.second << std::endl;

  //   int max_num = 65535;
  //   int offset = divfactor.first;
  //   auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
  //   auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, offset & max_num);
  //   auto inst1 = new SemiMachineInstruction("movw", inst1_dst, inst1_oprand1);
  //   semiblock.addInstruction(inst1);
  //   int high_num = (unsigned int)offset >> 16;
  //   // if (high_num != 0) {
  //   // auto inst1 = "\tmovt\tlr, #" + std::to_string(high_num);
  //   // * movt lr, #high_num
  //   auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, //
  //                                          "lr");
  //   auto inst2_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, high_num);
  //   auto inst2 = new SemiMachineInstruction("movt", inst2_dst, inst2_oprand1);
  //   semiblock.addInstruction(inst2);
  //   // }
  //   // Now, lr = mm
  //   // and next comes:
  //   // smull lr, dst, lr, s1_src_reg
  //   // add dst, dst, s1_src_reg
  //   // asr dst, dst, divfactor.second
  //   // sub dst, dst, asr, #31

  //   auto inst3_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "lr, " + dt);
  //   auto inst3_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
  //   auto inst3_oprand2 =
  //       new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, s1_src_reg->getPrintableString());
  //   auto inst3 = new SemiMachineInstruction("smull", inst3_dst, inst3_oprand1, inst3_oprand2);

  //   auto inst4_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  //   auto inst4_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  //   auto inst4_oprand2 =
  //       new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, s1_src_reg->getPrintableString());
  //   auto inst4 = new SemiMachineInstruction("add", inst4_dst, inst4_oprand1, inst4_oprand2);

  //   auto inst5_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  //   auto inst5_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  //   auto inst5_oprand2 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, divfactor.second);
  //   auto inst5 = new SemiMachineInstruction("asr", inst5_dst, inst5_oprand1, inst5_oprand2);

  //   auto inst6_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  //   auto inst6_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  //   auto inst6_oprand2 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other,
  //                                              s1_src_reg->getPrintableString() + ", asr #31");
  //   auto inst6 = new SemiMachineInstruction("sub", inst6_dst, inst6_oprand1, inst6_oprand2);

  //   semiblock.addInstruction(inst3);
  //   semiblock.addInstruction(inst4);
  //   semiblock.addInstruction(inst5);
  //   semiblock.addInstruction(inst6);
  //   // std::cout << inst1->getInstruction() << std::endl;
  //   // std::cout << inst2->getInstruction() << std::endl;
  //   // std::cout << inst3->getInstruction() << std::endl;
  //   // std::cout << inst4->getInstruction() << std::endl;
  //   // std::cout << inst5->getInstruction() << std::endl;
  //   // std::cout << inst6->getInstruction() << std::endl;
  //   return semiblock;
  // } else {
  //   auto s2_src_reg = GetOperand(s2, semiblock);
  //   auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  //   auto inst1 = new SemiMachineInstruction("sdiv", inst1_dst, s1_src_reg, s2_src_reg);
  //   semiblock.addInstruction(inst1);

  //   return semiblock;
  // }
}
#else
#ifdef REGALLOC
SemiMachineBlock IRToSemiSDiv(Instruction *instruction_item) {
  assert(instruction_item->getOpcode() == Instruction::SDiv && "this instruction should be a DIV");
  // assert(instruction_item->Color == 0 && "div inst should be allocated at r0");
  SemiMachineBlock semiblock = SemiMachineBlock();
  // save
  semiblock.addInstruction(new SemiMachineInstruction("\tpush\t{r0, r1, r2, r3}", 0, SemiMachineInstruction::St_));
  auto s1 = instruction_item->getNumOperand(0).get();
  auto s2 = instruction_item->getNumOperand(1).get();
  std::string s1_src_reg, s2_src_reg;
  if ((HasRegAllocated(s1) && s1->getColor() != 0) || isa<ConstantInt>(s1)) {
    s1_src_reg = GetOperand(s1, semiblock);
    if (s1_src_reg == "lr") {
      auto new_mov = new SemiMachineInstruction("\tmov\tr11, " + s1_src_reg, 0, SemiMachineInstruction::Cmp_);
      semiblock.addInstruction(new_mov);
      s1_src_reg = "r11";
    }
    // semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr0, " + GetOperand(s1,
    // semiblock),0,SemiMachineInstruction::Mov_));
  }
  if ((HasRegAllocated(s2) && s2->getColor() != 0) || isa<ConstantInt>(s2)) {
    s2_src_reg = GetOperand(s2, semiblock);
    // semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr1, " + GetOperand(s2,
    // semiblock),0,SemiMachineInstruction::Mov_));
  }
  if (s1_src_reg != "r1" && s2_src_reg == "r0") {
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr1, r0", 0, SemiMachineInstruction::Mov_));
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr0, " + s1_src_reg, 0, SemiMachineInstruction::Mov_));
  } else if (s1_src_reg == "r1" && s2_src_reg == "r0") {
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr12, r0", 0, SemiMachineInstruction::Mov_));
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr0, r1", 0, SemiMachineInstruction::Mov_));
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr1, 12", 0, SemiMachineInstruction::Mov_));
  } else {
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr0, " + s1_src_reg, 0, SemiMachineInstruction::Mov_));
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr1, " + s2_src_reg, 0, SemiMachineInstruction::Mov_));
  }

  auto I3 = new SemiMachineInstruction("\tbl\t__aeabi_idiv", 0, SemiMachineInstruction::Br_);
  semiblock.addInstruction(I3);

  if (instruction_item->getColor() != 0) {
    semiblock.addInstruction(
        new SemiMachineInstruction("\tmov\t" + instruction_item->getReg() + ", r0", 0, SemiMachineInstruction::Mov_));
  }

  // restore
  semiblock.addInstruction(new SemiMachineInstruction("\tpop\t{r0, r1, r2, r3}", 0, SemiMachineInstruction::Ld_));

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
#endif

#ifdef REGALLOC
SemiMachineBlock IRToSemiAnd(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  return semiblock;
}
#else
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
#endif

#ifdef REGALLOC
SemiMachineBlock IRToSemiOr(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  return semiblock;
}
#else
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
#endif

#ifdef REGALLOC
// FIXME:
SemiMachineBlock IRToSemiXor(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Xor && "this instruction should be an XOR");
  std::cout << "Xor inst is used" << std::endl;
  return semiblock;
}
#else
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
#endif

SemiMachineBlock IRToSemiAlloca(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Alloca && "this instruction should be an Alloca");
  return semiblock;
}

#ifdef REGALLOC
SemiMachineBlock IRToSemiLoad(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  if (!instruction_item->SpilledAndUsedByCall) {
    assert(instruction_item->getOpcode() == Instruction::Load && "this instruction should be a Load");
    auto op1 = instruction_item->getNumOperand(0).get();
    // std::string inst1 = "\tldr\t" + instruction_item->getReg() + ", [" + GetOperand(op1, semiblock) + "]";
    // ldr instruction_item->getReg()  [" + GetOperand(op1, semiblock) + "]
    auto inst1_dst =
        new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, instruction_item->getReg());
    auto inst1_oprand1_temp = GetOperand(op1, semiblock);
    auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other,
                                               "[" + inst1_oprand1_temp->getPrintableString() + "]");
    // auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Ld_);
    auto inst1 = new SemiMachineInstruction("ldr", inst1_dst, inst1_oprand1);
    semiblock.addInstruction(inst1);
  }
  return semiblock;
}
#else
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
#endif

#ifdef REGALLOC
// FIXME:
SemiMachineBlock IRToSemiStore(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Store && "this instruction should be a Store");
  auto op1 = instruction_item->getNumOperand(0).get();
  auto op2 = instruction_item->getNumOperand(1).get();
  auto op2_reg = GetOperand(op2, semiblock);
  // std::string inst1 = "\tstr\t" + GetOperand(op1, semiblock) + ", [" + op2_reg + "]";
  // st []
  auto inst1_dst = GetOperand(op1, semiblock);
  auto inst1_oprand1 =
      new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "[" + op2_reg->getPrintableString() + "]");
  // auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::St_);
  auto inst1 = new SemiMachineInstruction("str", inst1_dst, inst1_oprand1);
  semiblock.addInstruction(inst1);
  return semiblock;
}
#else
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
#endif

#ifdef REGALLOC
// if offset is constant ,
SemiMachineBlock IRToSemiGetElementPtr(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  auto GepI = cast<GetElementPtrInst>(instruction_item);
  assert(GepI && "this instruction should be a GEP");
  auto ptr = GepI->getNumOperand(0).get();
  auto offset = GepI->getOffset();
  if (auto const_offset = cast<ConstantInt>(offset)) {
    // semiblock += GetOperand(ptr, instruction_item->getColor());
    // std::string inst1 = "\tadd\t" + instruction_item->getReg() + ", " + GetOperand(ptr, semiblock) + ", " +
    //                     ProcessSpillOut(4 * const_offset->getValue(), semiblock);
    auto inst1_dst =
        new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, instruction_item->getReg());
    auto inst1_oprand1 = GetOperand(ptr, semiblock);
    auto inst1_oprand2 = ProcessSpillOut(4 * const_offset->getValue(), semiblock);
    // auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Add_);
    auto inst1 = new SemiMachineInstruction("add", inst1_dst, inst1_oprand1, inst1_oprand2);
    semiblock.addInstruction(inst1);
  } else {
    assert((isa<Instruction>(offset) || isa<Argument>(offset)) &&
           "Offset of gep should be return result of another inst");

    // std::string inst = "\tlsl\tr12, " + GetOperand(offset, semiblock) + ", #2";
    // lsl r12, GetOperand(off) #2
    auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r12");
    auto inst1_oprand1 = GetOperand(offset, semiblock);
    auto inst1_oprand2 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, 2);
    // semiblock.addInstruction(new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Lsl_));
    auto inst1 = new SemiMachineInstruction("lsl", inst1_dst, inst1_oprand1, inst1_oprand2);
    semiblock.addInstruction(inst1);
    // assert(isa<Instruction>(ptr) && "ptr is not inst");
    // assert(HasRegAllocated(ptr) && "ptr is not in reg");
    semiblock += GetOperand(ptr, instruction_item->getColor());
    // std::string inst1 = "\tadd\t" + instruction_item->getReg() + ", " + instruction_item->getReg() + ", r12";
    auto inst2_dst =
        new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, instruction_item->getReg());
    auto inst2_oprand1 =
        new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, instruction_item->getReg());
    auto inst2_oprand2 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r12");
    auto inst2 = new SemiMachineInstruction("add", inst2_dst, inst2_oprand1, inst2_oprand2);

    // semiblock.addInstruction(new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Add_));
    semiblock.addInstruction(inst2);
  }
  return semiblock;
}
#else
// FIXME:
SemiMachineBlock IRToSemiGetElementPtr(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  auto GepI = cast<GetElementPtrInst>(instruction_item);
  assert(GepI && "this instruction should be a GEP");
  auto ptr = GepI->getNumOperand(0).get();
  auto offset = GepI->getOffset();
  if (auto const_offset = cast<ConstantInt>(offset)) {
    semiblock += GetOperand(ptr, 1);
    std::string inst1 = "\tadd\tr1, r1, " + ProcessSpillOut(4 * const_offset->getValue(), 4, semiblock);
    auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Add_);
    semiblock.addInstruction(I1);
    semiblock += StoreTempValue(instruction_item, 1);
  } else {
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
#endif

#ifdef REGALLOC
// 1. 对于4个以后的参数，创建str指令保存到栈中：地址为(i - 4) * 4 + sp
// 2. 无条件push r0
// 3. 对于r1-r3中，如果用到就保存起来（push）
// 4. 通过使用r12作为中转进行交换：mov  r12, r0 | mov  r0, r1 | mov r1, r12
SemiMachineBlock IRToSemiCall(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Call && "this instruction should be a Call");
  std::string save_inst = "r0";
  int call_saved_regs_num = 1;
  auto func_called = cast<Function>(instruction_item->getNumOperand(-1).get());
  if (func_called->isDeclaration()) {
    save_inst = "r0, r1, r2, r3";
    call_saved_regs_num = 3;
  } else {
    for (int i = 1; i < instruction_item->getNumOperands() - 1 && i < 4; i++) {
      save_inst += ", r" + std::to_string(i);
      call_saved_regs_num = i;
    }
  }

  // std::cout << "called gunction is " << func_called->getName() << std::endl;

  auto *CI = cast<CallInst>(instruction_item);
  for (int i = 4; i < instruction_item->getNumOperands() - 1; i++) {
    std::string inst;
    if (instruction_item->getNumOperand(i).get()->SpilledAndUsedByCall) {
      auto load_param = cast<LoadInst>(instruction_item->getNumOperand(i).get());
      assert(load_param && "my param is not a load inst");
      assert(load_param->getOpcode() == Instruction::Load && "this instruction should be a Load");
      auto op1 = load_param->getNumOperand(0).get();
      auto dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, load_param->getReg());
      auto src1 = GetOperand(op1, semiblock);
      src1->setTag("[" + src1->getPrintableString() + "]");
      // std::string inst1 = "\tldr\t" + load_param->getReg() + ", [" + GetOperand(op1, semiblock) + "]";
      auto I1 = new SemiMachineInstruction("ldr", dst, src1);
      semiblock.addInstruction(I1);
    }
    // inst = "\tstr\t" + GetOperand(instruction_item->getNumOperand(i).get(), semiblock) + ", [sp, " +
    //        ProcessSpillOut((i - 4) * 4, semiblock) + "]";
    // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::St_);
    auto inst1_dst = GetOperand(instruction_item->getNumOperand(i).get(), semiblock);
    auto inst1_oprand1_temp = ProcessSpillOut((i - 4) * 4, semiblock);
    auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other,
                                               "[sp, " + inst1_oprand1_temp->getPrintableString() + "]");
    auto inst1 = new SemiMachineInstruction("str", inst1_dst, inst1_oprand1);
    semiblock.addInstruction(inst1);
  }
  // semiblock.addInstruction(new SemiMachineInstruction("\tpush\t{" + save_inst + "}", 0,
  // SemiMachineInstruction::St_));
  auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "{" + save_inst + "}");
  auto inst2 = new SemiMachineInstruction("push", inst2_dst);
  // std::cout << save_inst << std::endl;
  semiblock.addInstruction(inst2);

  for (int i = 0; i < instruction_item->getNumOperands() - 1 && i < 4; i++) {
    auto Operand_i = instruction_item->getNumOperand(i).get();
    if (Operand_i->SpilledAndUsedByCall) {
      auto this_op = cast<LoadInst>(Operand_i);
      assert(this_op && "func param is not load inst");
      auto op_ptr = this_op->getNumOperand(0).get();
      auto AI = cast<AllocaInst>(op_ptr);
      auto offset = temp_value[AI];
      offset = current_func_alloc_size - offset;
      // auto inst = "\tadd\tr12, sp, " + ProcessSpillOut(offset + 4 * (call_saved_regs_num + 1), semiblock);
      auto inst3_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r12");
      auto inst3_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "sp");
      auto inst3_oprand2 = ProcessSpillOut(offset + 4 * (call_saved_regs_num + 1), semiblock);
      auto inst3 = new SemiMachineInstruction("add", inst3_dst, inst3_oprand1, inst3_oprand2);
      // auto I = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Add_);
      semiblock.addInstruction(inst3);

      std::string register_name = "r" + std::to_string(i);
      auto inst4_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
      auto inst4_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "[r12]");
      auto inst4 = new SemiMachineInstruction("ldr", inst4_dst, inst4_oprand1);
      // semiblock.addInstruction(
      //     new SemiMachineInstruction("\tldr\tr" + std::to_string(i) + ", [r12]", 0, SemiMachineInstruction::Ld_));
      semiblock.addInstruction(inst4);
      continue;
    }

    if (auto CO = cast<ConstantInt>(Operand_i)) {
      std::string register_name = "r" + std::to_string(i);
      auto inst5_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
      auto inst5_oprand1 = ProcessSpillOut(CO->getValue(), semiblock);
      // semiblock.addInstruction(
      //     new SemiMachineInstruction("\tmov\tr" + std::to_string(i) + ", " + ProcessSpillOut(CO->getValue(),
      //     semiblock), 0, SemiMachineInstruction::Mov_));
      auto inst5 = new SemiMachineInstruction("mov", inst5_dst, inst5_oprand1);
      semiblock.addInstruction(inst5);
    } else {
      assert(HasRegAllocated(Operand_i) && "func param doesn't have reg allocated");
      if (Operand_i->getColor() < i) {
        // semiblock.addInstruction(new SemiMachineInstruction(
        //     "\tldr\tr" + std::to_string(i) + ", [sp, " + ProcessSpillOut(Operand_i->getColor() * 4, semiblock) +
        //     "]", 0, SemiMachineInstruction::Ld_));
        std::string register_name = "r" + std::to_string(i);
        auto inst6_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
        auto inst6_oprand1_temp = ProcessSpillOut(Operand_i->getColor() * 4, semiblock);
        auto inst6_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other,
                                                   "[sp, " + inst6_oprand1_temp->getPrintableString() + "]");
        auto inst6 = new SemiMachineInstruction("ldr", inst6_dst, inst6_oprand1);
        semiblock.addInstruction(inst6);
      } else {
        std::string register_name = "r" + std::to_string(i);
        auto inst7_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, register_name);
        auto inst7_oprand1 =
            new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, Operand_i->getReg());
        // semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr" + std::to_string(i) + ", " +
        // Operand_i->getReg(),
        //                                                     0, SemiMachineInstruction::Ld_));
        auto inst7 = new SemiMachineInstruction("mov", inst7_dst, inst7_oprand1);
        semiblock.addInstruction(inst7);
      }
    }
    // semiblock += GetOperand(instruction_item->getNumOperand(i).get(), i);
  }
  std::string func_name, inst1;
  func_name = instruction_item->getNumOperand(-1)->getName();
  // inst1 = "\tbl\t" + func_name;
  // * bl fuinc_name
  // auto I = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Br_);
  auto inst8_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, func_name);
  auto inst8 = new SemiMachineInstruction("bl", inst8_dst);
  semiblock.addInstruction(inst8);

  if (!CI->getFunctionType()->isReturnVoid()) {
    // semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr12, r0", 0, SemiMachineInstruction::Mov_));
    auto inst9_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r12");
    auto inst9_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r0");
    auto inst9 = new SemiMachineInstruction("mov", inst9_dst, inst9_oprand1);
    semiblock.addInstruction(inst9);
  }
  // semiblock.addInstruction(new SemiMachineInstruction("\tpop\t{" + save_inst + "}", 0,
  // SemiMachineInstruction::Ld_));
  auto inst10_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "{" + save_inst + "}");
  auto inst10 = new SemiMachineInstruction("pop", inst10_dst);
  semiblock.addInstruction(inst10);

  if (!CI->getFunctionType()->isReturnVoid()) {
    // semiblock.addInstruction(
    //     new SemiMachineInstruction("\tmov\t" + instruction_item->getReg() + ", r12", 0,
    //     SemiMachineInstruction::Mov_));
    auto inst11_dst =
        new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, instruction_item->getReg());
    auto inst11_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r12");
    auto inst11 = new SemiMachineInstruction("mov", inst11_dst, inst11_oprand1);
    semiblock.addInstruction(inst11);
  }
  return semiblock;
}
#else
SemiMachineBlock IRToSemiCall(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::Call && "this instruction should be a Call");
  for (int i = 0; i < instruction_item->getNumOperands() - 1; i++) {
    std::string inst;
    if (i < 4) {
      semiblock += GetOperand(instruction_item->getNumOperand(i).get(), i);
    } else {
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
#endif

#ifdef REGALLOC
SemiMachineBlock IRToSemiZExt(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  auto ZExtI = cast<ZExtInst>(instruction_item);
  assert(ZExtI && "this instruction should be an Ext");
  auto s1 = instruction_item->getNumOperand(0).get();
  auto IcmpI = cast<ICmpInst>(s1);

  // auto I2 =
  //     new SemiMachineInstruction("\tmov\t" + instruction_item->getReg() + ", #0", 0, SemiMachineInstruction::Mov_);
  // semiblock.addInstruction(I2);
  auto inst1_dst =
      new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, instruction_item->getReg());
  auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, 0);
  auto inst1 = new SemiMachineInstruction("mov", inst1_dst, inst1_oprand1);

  auto inst2_opcode = "mov" + IcmpI->getCmpType_codegen();
  auto inst2_dst =
      new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, instruction_item->getReg());
  auto inst2_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Constant, 1);
  auto inst2 = new SemiMachineInstruction(inst2_opcode, inst2_dst, inst2_oprand1);
  // auto I3 =
  //     new SemiMachineInstruction("\tmov" + IcmpI->getCmpType_codegen() + "\t" + +", #1", 0,
  //                                SemiMachineInstruction::Mov_);
  // semiblock.addInstruction(I3);

  return semiblock;
}
#else
// 不需要翻译
SemiMachineBlock IRToSemiZExt(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  return semiblock;
}
#endif

#ifdef ARM_V8
SemiMachineBlock IRToSemiSRem(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::SRem && "this instruction should be a SRem");
  auto s1 = instruction_item->getNumOperand(0).get();
  auto s2 = instruction_item->getNumOperand(1).get();
  auto dt = instruction_item->getReg();

  // std::string s1_src_reg = GetOperand(s1, semiblock);
  auto s1_src_reg = GetOperand(s1, semiblock);
  if (s1_src_reg->getPrintableString() == "lr" || s1_src_reg->getPrintableString() == "r12") {
    // auto new_mov = new SemiMachineInstruction("\tmov\tip, " + s1_src_reg, 0, SemiMachineInstruction::Cmp_);
    auto new_mov_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
    auto new_mov = new SemiMachineInstruction("mov", new_mov_dst, s1_src_reg);
    semiblock.addInstruction(new_mov);
    // s1_src_reg = "ip";
    s1_src_reg = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "ip");
  }
  // std::string s2_src_reg = GetOperand(s2, semiblock);
  auto s2_src_reg = GetOperand(s2, semiblock);

  // std::string temp_reg;
  SemiMachineOprand *temp_reg;
  if (s2_src_reg->getPrintableString() != "lr") {
    // temp_reg = "lr";
    temp_reg = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "lr");
  } else {
    // temp_reg = "r12";
    temp_reg = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r12");
  }

  std::string temp_name = temp_reg->getPrintableString();
  std::string s1_src_reg_name = s1_src_reg->getPrintableString();
  std::string s2_src_reg_name = s2_src_reg->getPrintableString();

  // auto I3 = new SemiMachineInstruction("\tsdiv\t" + temp_reg + ", " + s1_src_reg + ", " + s2_src_reg, 0,
  //                                      SemiMachineInstruction::Div_);
  // semiblock.addInstruction(I3);
  // auto I4 = new SemiMachineInstruction("\tmul\t" + temp_reg + ", " + temp_reg + ", " + s2_src_reg, 0,
  //                                      SemiMachineInstruction::Mul_);
  // semiblock.addInstruction(I4);
  // auto I5 =
  //     new SemiMachineInstruction("\tsub\t" + dt + ", " + s1_src_reg + ", " + temp_reg, 0,
  //     SemiMachineInstruction::Sub_);
  // semiblock.addInstruction(I5);

  auto inst1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, temp_name);
  auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, s1_src_reg_name);
  auto inst1_oprand2 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, s2_src_reg_name);
  auto inst1 = new SemiMachineInstruction("sdiv", inst1_dst, inst1_oprand1, inst1_oprand2);

  auto inst2_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, temp_name);
  auto inst2_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, temp_name);
  auto inst2_oprand2 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, s2_src_reg_name);
  auto inst2 = new SemiMachineInstruction("mul", inst2_dst, inst2_oprand1, inst2_oprand2);

  auto inst3_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, dt);
  auto inst3_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, s1_src_reg_name);
  auto inst3_oprand2 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, temp_name);
  auto inst3 = new SemiMachineInstruction("sub", inst3_dst, inst3_oprand1, inst3_oprand2);

  semiblock.addInstruction(inst1);
  semiblock.addInstruction(inst2);
  semiblock.addInstruction(inst3);

  delete s1_src_reg;
  delete s2_src_reg;
  delete temp_reg;

  return semiblock;
}
#else
#ifdef REGALLOC
SemiMachineBlock IRToSemiSRem(Instruction *instruction_item) {

  SemiMachineBlock semiblock = SemiMachineBlock();
  assert(instruction_item->getOpcode() == Instruction::SRem && "this instruction should be a Rem");
  // save
  semiblock.addInstruction(new SemiMachineInstruction("\tpush\t{r0, r1, r2, r3}", 0, SemiMachineInstruction::St_));
  auto s1 = instruction_item->getNumOperand(0).get();
  auto s2 = instruction_item->getNumOperand(1).get();
  std::string s1_src_reg, s2_src_reg;
  if ((HasRegAllocated(s1) && s1->getColor() != 0) || isa<ConstantInt>(s1)) {
    s1_src_reg = GetOperand(s1, semiblock);
    if (s1_src_reg == "lr") {
      auto new_mov = new SemiMachineInstruction("\tmov\tr11, " + s1_src_reg, 0, SemiMachineInstruction::Cmp_);
      semiblock.addInstruction(new_mov);
      s1_src_reg = "r11";
    }
  }
  if ((HasRegAllocated(s2) && s2->getColor() != 0) || isa<ConstantInt>(s2)) {
    s2_src_reg = GetOperand(s2, semiblock);
  }
  if (s1_src_reg != "r1" && s2_src_reg == "r0") {
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr1, r0", 0, SemiMachineInstruction::Mov_));
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr0, " + s1_src_reg, 0, SemiMachineInstruction::Mov_));
  } else if (s1_src_reg == "r1" && s2_src_reg == "r0") {
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr12, r0", 0, SemiMachineInstruction::Mov_));
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr0, r1", 0, SemiMachineInstruction::Mov_));
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr1, 12", 0, SemiMachineInstruction::Mov_));
  } else {
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr0, " + s1_src_reg, 0, SemiMachineInstruction::Mov_));
    semiblock.addInstruction(new SemiMachineInstruction("\tmov\tr1, " + s2_src_reg, 0, SemiMachineInstruction::Mov_));
  }

  auto I3 = new SemiMachineInstruction("\tbl\t__aeabi_idivmod", 0, SemiMachineInstruction::Br_);
  semiblock.addInstruction(I3);
  if (instruction_item->getColor() != 0) {
    semiblock.addInstruction(
        new SemiMachineInstruction("\tmov\t" + instruction_item->getReg() + ", r1", 0, SemiMachineInstruction::Mov_));
  }

  // restore
  semiblock.addInstruction(new SemiMachineInstruction("\tpop\t{r0, r1, r2, r3}", 0, SemiMachineInstruction::Ld_));

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

  // FIXME:
  // lr作为大整数的暂存
  auto I3 = new SemiMachineInstruction("\tbl\t__aeabi_idivmod", 0, SemiMachineInstruction::Br_);
  semiblock.addInstruction(I3);
  // 注意：取模的时候，函数返回值在r1
  semiblock += StoreTempValue(instruction_item, 1);
  return semiblock;
}
#endif
#endif

SemiMachineBlock IRToSemiPHI(Instruction *instruction_item) {
  SemiMachineBlock semiblock = SemiMachineBlock();
  return semiblock;
}

SemiMachineBlock ReslovePhiNode(Instruction *instruction_item) {
  SemiMachineBlock instruction = SemiMachineBlock();
  if (instruction_item->isTerminator()) {
    auto basic_block_item = instruction_item->getParent();
    // std::cout << ">> At BB: " << basic_block_item->getName() << std::endl;
    int reg_used_times[12];
    for (int i = 0; i < 12; i++)
      reg_used_times[i] = -1;

    for (auto each : basic_block_item->Phi_use) {
      auto phi_to = each.first;
      auto phi_from = each.second;
      assert((isa<Instruction>(phi_from) || isa<ConstantInt>(phi_from) || isa<Argument>(phi_from)) &&
             "Phi's value is not expected.");
      if (!phi_to->isPHISpilled) {
        reg_used_times[phi_to->getColor()] = 0;
        if (!isa<ConstantInt>(phi_from)) {
          reg_used_times[phi_from->getColor()] = 0;
        }
      }
    }

    std::map<int, Value *> mov_inst;
    for (auto each : basic_block_item->Phi_use) {
      auto phi_to = each.first;
      auto phi_from = each.second;
      assert((isa<Instruction>(phi_from) || isa<ConstantInt>(phi_from) || isa<Argument>(phi_from)) &&
             "Phi's value is not expected.");
      if (phi_to->isPHISpilled) {
        std::string inst;
        SemiMachineOprand *phi_mov_dst;
        if (auto CSI = cast<ConstantInt>(phi_from)) {
          instruction += GetOperand(phi_to->SpilledAI, 12);
          // inst = "\tstr\t" + GetOperand(CSI, instruction) + ", [r12]";
          phi_mov_dst = GetOperand(CSI, instruction);
        } else {
          if (phi_from->isSpilled) {
            auto spill_alloca = phi_from->SpilledAI;
            // std::string inst1 = "\tldr\tr11, [" + GetOperand(spill_alloca, instruction) + "]";
            // auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Ld_);

            auto temp_inst_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r11");
            auto temp_inst_oprand1_temp = GetOperand(spill_alloca, instruction);
            auto temp_inst_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other,
                                                           "[" + temp_inst_oprand1_temp->getPrintableString() + "]");
            //  instruction.addInstruction(I1);
            auto temp_inst = new SemiMachineInstruction("ldr", temp_inst_dst, temp_inst_oprand1);
            instruction.addInstruction(temp_inst);

            instruction += GetOperand(phi_to->SpilledAI, 12);
            // inst = "\tstr\tr11, [r12]";
            phi_mov_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r11");
          } else {
            instruction += GetOperand(phi_to->SpilledAI, 12);
            // inst = "\tstr\tr" + std::to_string(phi_from->getColor()) + ", [r12]";
            phi_mov_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register,
                                                "r" + std::to_string(phi_from->getColor()));
          }
        }
        // instruction.addInstruction(new SemiMachineInstruction(inst, 0, SemiMachineInstruction::St_));
        auto phi_mov_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other, "[r12]");

        auto phi_mov_inst = new SemiMachineInstruction("mov", phi_mov_dst, phi_mov_oprand1);
        instruction.addInstruction(phi_mov_inst);
      } else if (auto CI = cast<ConstantInt>(phi_from)) {
        int dest_reg = phi_to->getColor();
        mov_inst.insert({dest_reg, CI});
      } else {
        int src_reg = phi_from->getColor();
        int dest_reg = phi_to->getColor();
        // std::cout << "src_reg = " << src_reg << std::endl;
        if (!phi_from->isSpilled)
          reg_used_times[src_reg]++;
        mov_inst.insert({dest_reg, phi_from});
      }
    }

    int saved_in_reg12 = -1;
    while (!mov_inst.empty()) {
      int left_val = 12, min = 15;
      for (int i = 0; i < 12; i++) {
        if (mov_inst.count(i) && reg_used_times[i] < min) {
          left_val = i;
          min = reg_used_times[i];
        }
      }
      assert(mov_inst.count(left_val) && "left_val wrong!");
      Value *right_val = mov_inst[left_val];
      assert(right_val && "right_val is null!");
      // std::cout << "  reg_used_times[" << left_val << "] = " << reg_used_times[left_val] << std::endl;
      if (reg_used_times[left_val] == 0) {
        std::string inst;
        SemiMachineOprand *register_pos;
        if (auto CI = cast<ConstantInt>(right_val))
          // inst = "\tmov\tr" + std::to_string(left_val) + ", " + ProcessSpillOut(CI->getValue(), instruction);
          register_pos = ProcessSpillOut(CI->getValue(), instruction);
        else if (right_val->isSpilled) {
          auto spill_alloca = right_val->SpilledAI;

          // std::string inst1 = "\tldr\tr11, [" + GetOperand(spill_alloca, instruction) + "]";
          // ldr r11, [GetOperand(spill_alloca, instruction)]
          auto inst1_oprand1_temp = GetOperand(spill_alloca, instruction);
          auto inst1_oprand1_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r11");
          auto inst1_oprand1 = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Other,
                                                     "[" + inst1_oprand1_temp->getPrintableString() + "]");
          // auto I1 = new SemiMachineInstruction(inst1, 0, SemiMachineInstruction::Ld_);
          auto inst1 = new SemiMachineInstruction("ldr", inst1_oprand1_dst, inst1_oprand1);
          instruction.addInstruction(inst1);

          // inst = "\tmov\tr" + std::to_string(left_val) + ", r11";
          register_pos = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r11");
        } else if (right_val->getColor() != saved_in_reg12)
          // inst = "\tmov\tr" + std::to_string(left_val) + ", r" + std::to_string(right_val->getColor());
          register_pos = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register,
                                               "r" + std::to_string(right_val->getColor()));
        else
          // inst = "\tmov\tr" + std::to_string(left_val) + ", r12";
          register_pos = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r12");
        // std::cout << "  - INST: " << inst << std::endl;
        if (!isa<Constant>(right_val) && !right_val->isSpilled) {
          reg_used_times[right_val->getColor()]--;
        }
        reg_used_times[left_val] = -1;
        mov_inst.erase(mov_inst.find(left_val));
        // std::cout << "  remove: " << left_val << std::endl;
        auto register_dst =
            new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r" + std::to_string(left_val));
        // auto new_mov = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
        auto new_mov = new SemiMachineInstruction("mov", register_dst, register_pos);
        instruction.addInstruction(new_mov);
      } else {
        std::string inst = "\tmov\tr12, r" + std::to_string(left_val);
        saved_in_reg12 = left_val;
        // std::cout << "saved_in_reg12 = " << saved_in_reg12 << std::endl;
        reg_used_times[left_val]--;
        auto new_mov_dst = new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r12");
        auto new_move_oprand1 =
            new SemiMachineOprand(SemiMachineOprand::SemiMachineOprandType::Register, "r" + std::to_string(left_val));
        // auto new_mov = new SemiMachineInstruction(inst, 0, SemiMachineInstruction::Mov_);
        auto new_mov = new SemiMachineInstruction("mov", new_mov_dst, new_move_oprand1);
        instruction.addInstruction(new_mov);
      }
    }
  }
  // new SemiMachineInstruction("\tmov\tr3, #1", 0, SemiMachineInstruction::Mov_);
  return instruction;
}

SemiMachineBlock InstructionToSemiMachine(Instruction *instruction_item) {
  SemiMachineBlock instruction = SemiMachineBlock();
  if (instruction_item->getOpcode() == Instruction::Opcode::Ret) {
    return IRToSemiRet(instruction_item);
  }
  if (instruction_item->getOpcode() == Instruction::Opcode::Br) {
    return ReslovePhiNode(instruction_item) + IRToSemiBr(instruction_item);
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
  if (instruction_item->getOpcode() == Instruction::Opcode::PHI) {
    return instruction;
  }
  return instruction;
}
} // namespace semimachine
