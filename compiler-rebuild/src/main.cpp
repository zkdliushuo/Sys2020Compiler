#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Deadcode.h"
#include "DominatorTree.h"
#include "LLVMContext.h"
#include "LiveVar.h"
#include "Mem2Reg.h"
#include "Module.h"
#include "ModuleAnalyse.h"
#include "RegAssign.h"
#include "recognizer.h"
#include "PropConstant.h"
#include "CSE.h"
#include "LICM.h"
#include "SimplifyCFG.h"
#include "SimplifySpill.h"

#include "assembly_builder.h"
// #define Codegen_Debug

using namespace YAL;
using namespace std;
using namespace c1_recognizer;
using namespace syntax_tree;
using namespace std::literals::string_literals;

bool checkXor(Function *F) {
  for (auto BB : F->getBasicBlockList()) {
    for (auto I : BB->getInstList()) {
      std::string op = I->getOpcodeName();
      if (op == "xor") {
        return false;
      }
    }
  }
  return true;
}

bool checkGV(Module *m, Function *F) {
  auto GVlist = m->getGlobalList();
  for (auto BB : F->getBasicBlockList()) {
    for (auto I : BB->getInstList()) {
      for (auto U = I->user_begin(); U != I->user_end(); U++) {
        if (auto gv = cast<GlobalVariable>(*U)) {
          auto temp = std::find(GVlist.begin(), GVlist.end(), gv);
          if (temp == GVlist.end())
            return false;
        }
      }
    }
  }
  return true;
}

int checkBr(Function *F) {
  for (auto BB : F->getBasicBlockList()) {
    for (auto I : BB->getInstList()) {
      if (auto br = cast<BranchInst>(I)) {
        if (std::find(F->getBasicBlockList().begin(), F->getBasicBlockList().end(), br->getSuccessor(0)) == F->getBasicBlockList().end())
          return 6;
        if (br->getSuccessor(0)->getParent() != F)
          return 7;
        if (br->isConditional()) {
          if (br->getSuccessor(1)->getParent() != F)
            return 8;
          if (std::find(F->getBasicBlockList().begin(), F->getBasicBlockList().end(), br->getSuccessor(1)) == F->getBasicBlockList().end()){
            auto func_name = br->getSuccessor(1)->getName();
            if(func_name.empty()){
              return 90;
            }
            else if(func_name.at(0) == 't' ){
              return 91;
            }
            else if(func_name.at(0) == 'e' ){
              return 92;
            }
            else if(func_name.at(0) == 'i' ){
              return 93;
            }
            else if(func_name.at(0) == 'c' ){
              return 94;
            }
            else if(func_name.at(0) == 'b' ){
              return 95;
            }
            else if(func_name.at(0) == 'n' ){
              if (func_name.at(5) == 'w') return 133;
              if (func_name.at(5) == 'a') return 134;
              if (func_name.at(5) == 'o') return 135;
              return 96;
            }
            return 9;
          }
        }
      }
    }
  }
  return 1;
}

// 功能测试：compiler testcase.sy -S -o testcase.s
// 性能测试：compiler testcase.sy -S -o testcase.s -O2
// Debug：  compiler testcase.sy -S -D
int main(int argc, char **argv) {
  string target_path;
  string input_path;
  bool compile = false;
  bool assemble = true;
  bool opt = false;
  if (argc < 2) {
    std::cerr << "please input more arguments";
    return 0;
  }
  if (argv[2] == "-D"s) {
    compile = true;
    if (input_path.empty() && argc == 4) {
      input_path = argv[3];
    }
  } else if (argv[2] == "-o"s) {
    if (target_path.empty() && argc >= 4) {
      target_path = argv[3];
    }
    if (input_path.empty() && argc >= 5) {
      input_path = argv[4];
    }
  }
  if (argc > 5) {
    if (argv[5] == "-O2"s || argv[5] == "-o2"s) {
      opt = true;
    }
  }
  if (target_path.empty()) {
    auto pos = input_path.rfind('.');
    if (pos == std::string::npos) {
      std::cerr << argv[0] << ": input file " << input_path << " has unknown filetype!" << std::endl;
      return -1;
    } else {
      if (input_path.substr(pos) != ".sy" && input_path.substr(pos) != ".c") {
        std::cerr << argv[0] << ": input file " << input_path << " has unknown filetype!" << std::endl;
        return -1;
      }
      target_path = input_path.substr(0, pos);
      if (!compile) {
        target_path += ".s"s;
      }
    }
  }

  ifstream in_stream(input_path);
  recognizer c1r(in_stream);

  error_reporter err(cerr);
  if (!c1r.execute(err)) {
    cerr << "Parsing failed. Exiting." << endl;
    return 2;
  }

  auto ast = c1r.get_syntax_tree();

  // std::cout<<"Finish AST Building"<<std::endl;

  string name = input_path;
  name = name.substr(name.find_last_of("/\\") + 1);

  LLVMContext YAL_ctx;
  assembly_builder builder(YAL_ctx, err);

  builder.build(name, ast);
  auto module = builder.get_module();

  opt = true;
  if(opt){
    for (auto F : module->getFunctionList()) {
      // std::cout << ">>>>> Function: " << F->getName() << " >>>>>" << std::endl;
      if (F->getEntryBlock()) {
        int temp = checkBr(F);
        if (temp != 1) return temp;
        if (!checkGV(module.get(), F)) { return 88; }
        if (!checkXor(F)) { return 99; }
        F->setBlockOrder();
        DeadcodeEliminator deadcode = DeadcodeEliminator();
        deadcode.run(F);

        DominatorTree DT(F);
        
        MemoryPromoter mem2reg = MemoryPromoter();
        mem2reg.MemToReg(F, DT);

        PropConstant PC;
        PC.runOnFunction(*F);

        DeadcodeEliminator deadcode1 = DeadcodeEliminator();
        deadcode1.run(F);

        SimplifyCFG simplecfg = SimplifyCFG(F);
        simplecfg.run();
        DominatorTree DT1(F);

        LICM licm = LICM(F, DT1, module.get());
        licm.run();

        SimplifyCFG simplecfg1 = SimplifyCFG(F);
        simplecfg1.run();

        DominatorTree DT2(F);

        CommonSubexpressionElimination(F, DT2);

        RegAssign RA1(*F, &DT2);
        RA1.runOnFunction();
        
        SimplifySpill SP(*F);
        SP.run();
        if (!checkGV(module.get(), F)) { return 88; }
      }
    }
  }
  else{
    // std::cout << "line 125" << std::endl;
    for (auto F : module->getFunctionList()) {
      // std::cout << ">>>>> Function: " << F->getName() << " >>>>>" << std::endl;
      if (F->getEntryBlock()) {
        DeadcodeEliminator deadcode = DeadcodeEliminator();
        deadcode.run(F);
        DominatorTree DT(F);
        
        PropConstant PC;
        PC.runOnFunction(*F);

        DeadcodeEliminator deadcode1 = DeadcodeEliminator();
        deadcode1.run(F);

        RegAssign RA1(*F, &DT);
        RA1.runOnFunction();
      }
    }
  }


  std::error_code err_message;
  if (!module) {
    cerr << "Semantic failed. Exiting." << endl;
    return 3;
  }
  if (compile) {
    module->print(target_path);
    auto command_string = std::string("llvm-link ") + target_path + ".ll ../src/io.ll -o " + target_path + ".bc";
    std::system(command_string.c_str());
    command_string = std::string("llc ") + target_path + ".bc -filetype=obj";
    std::system(command_string.c_str());
    command_string = std::string("clang ") + target_path + ".o -o " + target_path;
    std::system(command_string.c_str());
    return 0;
  }
  if (assemble) {
    // std::cout << "moduleTransform" << std::endl;
    auto result = semimachine::moduleTransform(module.get());
    result.DeleteUselessInstruction();
    // std::cout << "Result.print" << std::endl;
    result.print(target_path);
    // std::cout << "deleteBlock" << std::endl;
    result.deleteBlock();
  }
  return 0;
}
