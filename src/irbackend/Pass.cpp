#include "Pass.h"
#include "Module.h"

using namespace YAL;

bool PassManager::run(Module& M){
    for(auto eachPass: PassList){
        if(!eachPass->runOnModule(M)){
            return false;
        }
    }
    return true;
}

bool FunctionPass::runOnModule(Module& M){
    for(auto everyFunction : M.getFunctionList()){
        if(!runOnFunction(*everyFunction)){
            return false;
        }
    }
    return true;
}

bool BasicBlockPass::runOnModule(Module& M){
    for(auto everyFunction : M.getFunctionList()){
        for(auto it = everyFunction->BB_begin();it != everyFunction->BB_end();it++){
            if(!runOnBasicBlock(*(*it))){
                return false;
            }
        }
    }
    return true;
}


