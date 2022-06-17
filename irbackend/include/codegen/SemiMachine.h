#ifndef CODEGEN_SEMIMACHINE_h
#define CODEGEN_SEMIMACHINE_h

#include <iostream>
#include <string>
#include <fstream>

#include "Instruction.h"

using namespace YAL;

namespace semimachine {
class SemiMachineInstruction {
public:
  enum SemiMachineType { Instruction = 0, FuncLabel, BBLabel, Variable };
  enum SemiMachineOpcode { Mov_ = 0, Add_, Sub_, Mul_, Div_, And_, Or_, Xor_, Ld_, St_, Br_, Cmp_, Nop_, Lsl_ };
  // enum SemiRegister {R0 = 0, R1, R2, R3, R4, lr, sp};

private:
  std::string inst;
  SemiMachineType type;
  SemiMachineOpcode op;
  SemiMachineInstruction *next_inst;

public:
  SemiMachineInstruction()
      : inst(""), type(SemiMachineType::Instruction), op(SemiMachineOpcode::Nop_), next_inst(nullptr) {}

  SemiMachineInstruction(std::string str, int t, int op)
      : inst(str), type(SemiMachineType::Instruction), op(SemiMachineOpcode::Nop_), next_inst(nullptr) {}

  // SemiMachineInstruction(std::string str, int t, int op)
  //     : inst(str), type(SemiMachineType::Instruction), op(SemiMachineOpcode::Nop_), next_inst(nullptr) {}

  std::string getInstruction() const { return inst; }
  SemiMachineInstruction *getNext() const { return next_inst; }

  void clearNext() { next_inst = nullptr; }
  void setInstruction(const std::string str) { inst = str; }
  void setNext(SemiMachineInstruction *next) { next_inst = next; }
  void setType(const int t) {
    switch (t) {
    case 0:
      type = SemiMachineType::Instruction;
      break;
    case 1:
      type = SemiMachineType::FuncLabel;
      break;
    case 2:
      type = SemiMachineType::BBLabel;
      break;
    case 3:
      type = SemiMachineType::Variable;
      break;
    default:
      type = SemiMachineType::Instruction;
    }
    next_inst = nullptr;
  }

  void addAttribute(const std::string str) {
    if (inst != "")
      inst += " ";
    inst += str;
  }
};
class SemiMachineBlock {
private:
  SemiMachineInstruction *head;
  SemiMachineInstruction *tail;

public:
  SemiMachineBlock() {
    head = nullptr;
    tail = nullptr;
  }

  ~SemiMachineBlock(){};

  SemiMachineInstruction *getHead() const { return head; }
  SemiMachineInstruction *getTail() const { return tail; }
  void setHead(SemiMachineInstruction *item) { head = item; }
  void setTail(SemiMachineInstruction *item) { tail = item; }

  void addInstruction(SemiMachineInstruction *inst);
  void deleteBlock();
  void operator+=(const SemiMachineBlock &other);

  unsigned getInstLineSize() {
    unsigned size = 0;
    auto item = head;
    for (; item != nullptr; item = item->getNext(), size++)
      ;
    return size;
  }

  void print(std::string target_path) {
    std::ofstream outfile;
    if(target_path.empty()){
        outfile.open("myfile.s");
    }
    else{
        outfile.open(target_path);
    }
    assert(outfile && "Can not open file");
    auto item = head;
    while (item != nullptr) {
      outfile << item->getInstruction() << std::endl;
      item = item->getNext();
    }
    outfile.close();
  }
};
extern SemiMachineBlock operator+(const SemiMachineBlock &block1, const SemiMachineBlock &block2);
extern SemiMachineBlock IRToSemiEntryBB();
extern SemiMachineBlock IRToSemiRetBB();
extern SemiMachineBlock InstructionToSemiMachine(Instruction *instruction_item);

} // namespace semimachine

#endif