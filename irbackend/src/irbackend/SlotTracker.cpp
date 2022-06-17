#include "SlotTracker.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "Value.h"

using namespace YAL;

SlotTracker::SlotTracker(const Function *F) : TheModule(F ? F->getParent() : nullptr), TheFunction(F) {}

int SlotTracker::getLocalSlot(const Value *V) {
    assert((!isa<Function>(V) || !isa<GlobalVariable>(V)) && "Function or Global Variable cannot use this local slot");
    ValueMap::iterator FI = fMap.find(V);
    return FI == fMap.end() ? -1 : (int)FI->second;
}

int SlotTracker::getGlobalSlot(const GlobalVariable *V) {
    ValueMap::iterator MI = mMap.find(V);
    return MI == mMap.end() ? -1 : (int)MI->second;
}

void SlotTracker::CreateFunctionSlot(const Value *V) {
    assert(!V->getType()->isVoidTy() && !V->hasName() && "Doesn't need a slot!");

    unsigned DestSlot = fNext++;
    fMap[V] = DestSlot;
}

void SlotTracker::initializeIfNeeded() {
    // std::cout << "initiliaze a function" << TheFunction->getName() <<std::endl;
    if (TheFunction && !FunctionProcessed)
        processFunction();
}

void SlotTracker::processFunction() {
    fNext = 0;

    for (auto it = TheFunction->Arg_begin(); it != TheFunction->Arg_end(); ++it)
        if (!(*it)->hasName())
            CreateFunctionSlot(*it);

    for (auto it = TheFunction->BB_begin(); it != TheFunction->BB_end(); it++) {
        for (auto I = (*it)->begin(); I != (*it)->end(); I++) {
            if (!(*I)->getType()->isVoidTy() && !(*I)->hasName())
                CreateFunctionSlot(*I);
        }
    }
    FunctionProcessed = true;
}

