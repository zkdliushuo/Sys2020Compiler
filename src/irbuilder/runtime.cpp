
#include <iostream>
#include <stdio.h>
#include "runtime.h"
// #include "runtime/io.h"

#include "Type.h"
#include "Constants.h"
#include "IRBuilder.h"

using namespace std;
using namespace YAL;

runtime_info::runtime_info(Module *module)
{
    getint_func = Function::Create(FunctionType::get(Type::getInt32Ty(module->getContext()),{},false),"getint",module);

    getch_func = Function::Create(FunctionType::get(Type::getInt32Ty(module->getContext()),{},false),"getch",module);

    getarray_func = Function::Create(FunctionType::get(Type::getInt32Ty(module->getContext()),
                                        {Type::getInt32PtrTy(module->getContext())},false),
                                        "getarray", module);
    
    putint_func = Function::Create(FunctionType::get(Type::getVoidTy(module->getContext()),
                                                          {Type::getInt32Ty(module->getContext())},
                                                          false),"putint",module);
    
    
    putch_func = Function::Create(FunctionType::get(Type::getVoidTy(module->getContext()),
                                                          {Type::getInt32Ty(module->getContext())},
                                                          false),
                                        "putch",module);
    
    putarray_func = Function::Create(FunctionType::get(Type::getVoidTy(module->getContext()),
                                                          {Type::getInt32Ty(module->getContext()), Type::getInt32PtrTy(module->getContext())},
                                                          false),
                                        "putarray",module);
    
    
    putf_func = Function::Create(FunctionType::get(Type::getVoidTy(module->getContext()),
                                                          true),
                                        "putf",module);
    
    
    starttime_func = Function::Create(FunctionType::get(Type::getVoidTy(module->getContext()),{Type::getInt32Ty(module->getContext())},
                                                          false),
                                        "_sysy_starttime",module);  
    
    
    stoptime_func = Function::Create(FunctionType::get(Type::getVoidTy(module->getContext()),{Type::getInt32Ty(module->getContext())},
                                                          false),
                                        "_sysy_stoptime",module);                                    
}

using namespace string_literals;

vector<tuple<string, YAL::Function *>> runtime_info::get_language_symbols()
{
    return {
        make_tuple("getint"s, getint_func),
        make_tuple("getch"s, getch_func),
        make_tuple("getarray"s, getarray_func),
        make_tuple("putint"s, putint_func),
        make_tuple("putch"s, putch_func),
        make_tuple("putarray"s, putarray_func),
        make_tuple("putf"s, putf_func),
        make_tuple("starttime"s, starttime_func),
        make_tuple("stoptime"s, stoptime_func)};
}
