#ifndef CODEGEN_SEMIMACHINE_h
#define CODEGEN_SEMIMACHINE_h

#include <fstream>
#include <iostream>
#include <string>

#include "Instruction.h"

using namespace YAL;

namespace semimachine {
class SemiMachineOprand {
public:
  enum SemiMachineOprandType { Constant = 0, Register, Other };

private:
  SemiMachineOprandType oprand_type;
  std::string tag;
  int val;

public:
  SemiMachineOprand() : oprand_type(SemiMachineOprandType::Constant), val(0), tag("") {
    // oprand_type = SemiMachineOprandType::Constant;
    // val = 0;
    // tag = "";
  }
  SemiMachineOprand(int type, int val) : oprand_type(static_cast<SemiMachineOprandType>(type)), val(val), tag("") {
    // std::cout << "constructing1: " << val << std::endl;
    // oprand_type = static_cast<SemiMachineOprandType>(type);
    // val = val;
    // tag = "";
  }
  SemiMachineOprand(SemiMachineOprandType type, int val) : oprand_type(type), val(val), tag("") {
    // std::cout << "constructing2: " << val << std::endl;
  }
  SemiMachineOprand(int type, std::string str)
      : oprand_type(static_cast<SemiMachineOprandType>(type)), val(0), tag(str) {
    // oprand_type = static_cast<SemiMachineOprandType>(type);
    // val = 0;
    // tag = str;
  }

  std::string getTag() { return tag; }
  int getType() { return oprand_type; }
  int getValue() { return val; }
  std::string getPrintableString() {
    // std::cout << "("
    //           << "oprand_type = " << oprand_type << ")" << std::endl;

    if (oprand_type == SemiMachineOprandType::Constant) {
      return "#" + std::to_string(val);
    } else {
      return tag;
    }
  }

  void setType(const int new_type) { oprand_type = static_cast<SemiMachineOprandType>(new_type); }
  void setConstant(const int new_val) { val = new_val; }
  void setTag(const std::string &new_tag) { tag = new_tag; }
};

class SemiMachineInstruction {
public:
  enum SemiMachineType { Instruction = 0, FuncLabel, BBLabel, Variable };
  enum SemiMachineOpcode { Mov_ = 0, Add_, Sub_, Mul_, Div_, And_, Or_, Xor_, Ld_, St_, Br_, Cmp_, Nop_, Lsl_ };
  // enum SemiRegister {R0 = 0, R1, R2, R3, R4, lr, sp};

private:
  SemiMachineType type;
  std::string op;
  SemiMachineOprand *dst;
  SemiMachineOprand *oprand1, *oprand2;
  SemiMachineInstruction *next_inst;

public:
  SemiMachineInstruction()
      : type(SemiMachineType::Instruction), op(""), dst(nullptr), oprand1(nullptr), oprand2(nullptr),
        next_inst(nullptr) {
    // type = SemiMachineType::Instruction;
    // op = "";
    // dst = nullptr;
    // oprand1 = nullptr;
    // oprand2 = nullptr;
    // next_inst = nullptr;
  }

  SemiMachineInstruction(const std::string str, SemiMachineOprand *const dst_)
      : type(SemiMachineType::Instruction), op(str), dst(dst_), oprand1(nullptr), oprand2(nullptr), next_inst(nullptr) {
    // type = SemiMachineType::Instruction;
    // op = str;
    // dst = dst_;
    // oprand1 = nullptr;
    // oprand2 = nullptr;
    // next_inst = nullptr;
  }

  SemiMachineInstruction(const std::string str, SemiMachineOprand *const dst_, SemiMachineOprand *const op1)
      : type(SemiMachineType::Instruction), op(str), dst(dst_), oprand1(op1), oprand2(nullptr), next_inst(nullptr) {
    // type = SemiMachineType::Instruction;
    // op = str;
    // dst = dst_;
    // oprand1 = op1;
    // oprand2 = nullptr;
    // next_inst = nullptr;
  }

  SemiMachineInstruction(const std::string str, SemiMachineOprand *const dst_, SemiMachineOprand *const op1,
                         SemiMachineOprand *const op2)
      : type(SemiMachineType::Instruction), op(str), dst(dst_), oprand1(op1), oprand2(op2), next_inst(nullptr) {
    // type = SemiMachineType::Instruction;
    // op = str;
    // dst = dst_;
    // oprand1 = op1;
    // oprand2 = op2;
    // next_inst = nullptr;
  }

  SemiMachineInstruction(const std::string str, int id)
      : type(static_cast<SemiMachineType>(id)), op(str), dst(nullptr), oprand1(nullptr), oprand2(nullptr),
        next_inst(nullptr) {
    // type = static_cast<SemiMachineType>(id);
    // op = str;
    // oprand1 = nullptr;
    // oprand2 = nullptr;
    // next_inst = nullptr;
  }

  SemiMachineInstruction(const std::string str, SemiMachineType id)
      : type(id), op(str), dst(nullptr), oprand1(nullptr), oprand2(nullptr), next_inst(nullptr) {
    // type = id;
    // op = str;
    // dst = nullptr;
    // oprand1 = nullptr;
    // oprand2 = nullptr;
    // next_inst = nullptr;
  }

  SemiMachineInstruction *getNext() const { return next_inst; }

  void clearNext() { next_inst = nullptr; }
  void setopcode(const std::string str) { op = str; }
  void setoprand1(SemiMachineOprand *const op1) { oprand1 = op1; }
  void setoprand2(SemiMachineOprand *const op2) { oprand2 = op2; }
  void setNext(SemiMachineInstruction *next) { next_inst = next; }
  void setType(const int t) { type = static_cast<SemiMachineType>(t); }

  void setInstruction(const std::string str) { op = str; }
  void addAttribute(const std::string str) { op += str; }

  SemiMachineOprand *getDst() { return dst; }
  SemiMachineOprand *getOp1() { return oprand1; }
  SemiMachineOprand *getOp2() { return oprand2; }
  std::string getOp() { return op; }
  std::string getInstruction() {
    // FIXME-Constider all situations
    // DONE: to be test
    if (type != SemiMachineType::Instruction) {
      return op;
    }

    std::string inst = "";
    inst += "\t" + op + "\t";

    inst += dst->getPrintableString();

    if (oprand1 != nullptr)
      inst += ", " + oprand1->getPrintableString();

    if (oprand2 != nullptr)
      inst += ", " + oprand2->getPrintableString();

    return inst;
  }
};

class SemiMachineBlock {
public:
  enum SemiMachineBlockLevel { InstructionLevelBlcok = 0, BasicBlockLevelBlcok, FunctionLevelBlcok, ModuleLevelBlcok };

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
    // std::cout << "write to " << target_path << std::endl;
    std::ofstream outfile;
    if (target_path.empty()) {
      outfile.open("myfile.s");
    } else {
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

  void DeleteUselessInstruction();
  void deleteInstruction(SemiMachineInstruction *inst);
};
extern SemiMachineBlock operator+(const SemiMachineBlock &block1, const SemiMachineBlock &block2);
extern SemiMachineBlock IRToSemiEntryBB();
extern SemiMachineBlock IRToSemiRetBB();
extern SemiMachineBlock InstructionToSemiMachine(Instruction *instruction_item);
} // namespace semimachine

#endif
