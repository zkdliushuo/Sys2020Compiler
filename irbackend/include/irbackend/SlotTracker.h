#ifndef YAL_IR_SLOTTRACKER_H
#define YAL_IR_SLOTTRACKER_H
#include "Constants.h"

#include <unordered_map>

using namespace YAL;
namespace YAL{
    class GlobalVariable;
    class Function;
    class SlotTracker {
        public:
        /// 映射类型：unorder_map
        using ValueMap = std::unordered_map<const Value *, unsigned>;

        private:
        /// 把Module传进来
        const Module *TheModule;

        /// 正在给哪个函数插数字
        const Function *TheFunction = nullptr;
        bool FunctionProcessed = false;

        /// 给模块中的全局变量的映射
        ValueMap mMap;
        unsigned mNext = 0;

        /// 给函数中的局部变量的映射
        ValueMap fMap;
        unsigned fNext = 0;

        public:
        /// SlotTracker构造函数 ，禁止隐式转换
        explicit SlotTracker(const Module *M) : TheModule(M) {}
        explicit SlotTracker(const Function *F) ;

        SlotTracker(const SlotTracker &) = delete;

        int getLocalSlot(const Value *V); 

        int getGlobalSlot(const GlobalVariable *V); 
        const Function *getFunction() const { return TheFunction; }

        void purgeFunction() {
            fMap.clear(); 
            TheFunction = nullptr;
            FunctionProcessed = false;
        }

        void setFunction(const Function * F){
            purgeFunction();
            assert(!TheFunction && "TheFunction is NULLPTR");
            TheFunction = F;
            initializeIfNeeded();
        }

        unsigned getfNext() {return fNext; }

        private:
        void CreateFunctionSlot(const Value *V) ;

        void processFunction();

        void initializeIfNeeded();
        
    };
}

#endif