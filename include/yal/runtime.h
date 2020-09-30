#ifndef _C1_RUNTIME_H_
#define _C1_RUNTIME_H_

#include <vector>
#include <tuple>

#include "GlobalVariable.h"
#include "Function.h"
#include "Module.h"

class runtime_info
{
  
    // YAL::GlobalVariable *input_ivar;
    // YAL::GlobalVariable *input_fvar;
    // YAL::GlobalVariable *output_ivar;
    // YAL::GlobalVariable *output_fvar;
    // YAL::Function *inputInt_func;
    // YAL::Function *inputFloat_func;
    // YAL::Function *outputInt_func;
    // YAL::Function *outputFloat_func;

    YAL::Function *getint_func;
    YAL::Function *getch_func;
    YAL::Function *getarray_func;
    YAL::Function *putint_func;
    YAL::Function *putch_func;
    YAL::Function *putarray_func;
    YAL::Function *putf_func;
    YAL::Function *starttime_func;
    YAL::Function *stoptime_func;

  public:
    runtime_info(YAL::Module *module);

    std::vector<std::tuple<std::string, YAL::Function *>> get_language_symbols();

    // std::vector<std::tuple<std::string, void *>> get_runtime_symbols();
};

#endif
