#ifndef YAL_IR_PASS_H
#define YAL_IR_PASS_H

#include <vector>
#include <string>

namespace YAL{
    
    class Module;
    class Function;
    class BasicBlock;

    enum PassKind {
        Pass_BasicBlock,
        Pass_Loop,
        Pass_Function,
        Pass_Module,
    };

    class Pass
    {
        const std::string PassID;
        PassKind Kind;
    public:
        explicit Pass(PassKind K, std::string pid) : PassID(pid), Kind(K) {}
        ~Pass() = default;
        virtual bool doInitialization(Module &)  { return false; }
        virtual bool doFinalization(Module &) { return false; }
        virtual bool runOnModule(Module &M) = 0;
    };

    class ModulePass : public Pass{
    public:
        explicit ModulePass(std::string pid) : Pass(Pass_Module , pid) {}
        ~ModulePass() = default;
        virtual bool runOnModule(Module &M) override = 0;
    };

    class FunctionPass : public Pass {
    public:
        explicit FunctionPass(std::string pid) : Pass(Pass_Function, pid) {}
        ~FunctionPass()  = default;
        virtual bool runOnFunction(Function &F) = 0;

        virtual bool runOnModule(Module &M) override final;
    };

    class BasicBlockPass : public Pass {
    public:
        explicit BasicBlockPass(std::string pid) : Pass(Pass_BasicBlock, pid) {}
        ~BasicBlockPass() = default;
        virtual bool runOnBasicBlock(BasicBlock &BB) = 0;

        virtual bool runOnModule(Module &M) override;
    };

    class PassManager{
    private:
        std::vector<Pass*> PassList;

    public:
        bool run(Module& M);
        void add(Pass* P) {
            PassList.push_back(P); 
        }

        // TODO
        /// Here should use a map mapping from a pid to a unique pass*
        void add(char &pid);
    };
}

#endif