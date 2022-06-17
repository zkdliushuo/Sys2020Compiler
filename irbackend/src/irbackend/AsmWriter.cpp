#include "Module.h"
#include "Function.h"
#include "support.h"
#include "GlobalVariable.h"
#include "BasicBlock.h"
#include "Instructions.h"
#include "SlotTracker.h"

#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace YAL;

std::ofstream outfile;

void writeLog(std::string target_name)
{ 
    if(target_name.empty()){
        outfile.open("../myfile.ll");
    }
    else{
        outfile.open(target_name);
    }
    assert(outfile && "Can not open file");
}
void closeLog()
{
    assert(outfile && "Can not open file");
    outfile.close();
}

// TODO
/// 实现Slot机制
enum PrefixType {
    GlobalPrefix,
    LabelPrefix,
    LocalPrefix,
    NoPrefix
};

void PrintName(std::string Name, PrefixType Prefix) {
    switch (Prefix) {
    case NoPrefix:
        break;
    case GlobalPrefix:
        outfile << '@';
        break;
    case LabelPrefix:
        break;
    case LocalPrefix:
        outfile << '%';
        break;
    }
    assert(!Name.empty() && "Name is empty");
    // std::cout << "PrintName: " << Name << std::endl;
    outfile << Name;
}

void PrintName(const Value* V) {
    if (isa<Function>(V) || isa<GlobalVariable>(V)) {
        // std::cout << "PrintName: is a Function or a GlobalVariable, Name : " << V->getName() << std::endl;
        PrintName(V->getName(), GlobalPrefix);
    }
    else
        PrintName(V->getName(), LocalPrefix);
}

namespace YAL
{
    /// 此文件用来处理IR的输出函数（可以暂时用源代码中的AsmWriter.cpp的相关函数代替，
    /// 因为输出IR并不是必要的，但是它能帮助我们验证程序的正确性）

    /// 需要使用：Module的Globallis和Functionlist
    /// 
    class AssemblyWriter {
    public:
        const Module *TheModule = nullptr;
        SlotTracker &Machine;
        AssemblyWriter(SlotTracker &Mac, const Module *M)
            : TheModule(M), Machine(Mac) { }

        /// 打印所有的全局变量和所有的函数
        // TODO
        /// 注意使用的时候需要建立UselistStack堆栈
        void printModule(const Module *M);
        void printFunction(const Function *F);

        /// 打印一个global变量，形如：@a = global i32 0 或者 @x = constant i32 4 
        /// 或者 @field = global [2 x i32] zeroinitializer
        /// 或者 @a = global [25 x i32] 
        /// [i32 1, i32 2, i32 3, i32 4, i32 5, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0]
        /// 因此，对于全局变量不需要为externelLinkage
        void printGlobal(const GlobalVariable *GV);

        /// 打印类型的函数
        void printType(const Type* Ty);

        /// 打印函数的参数
        void printArgument(const Argument *Arg);

        /// 打印基本块的函数
        void printBasicBlock(const BasicBlock *BB);

        /// 打印一条指令行
        void printInstructionLine(const Instruction *I);

        /// 打印一条指令
        void printInstruction(const Instruction *I);

        /// 打印一个操作数
        void writeOperand(const Value *Operand, bool PrintType);

        /// 打印参数
        void writeParamOperand(const Value *Operand);

        /// 把这个操作数作为常数打印
        void WriteConstant(const Constant *CV);

        /// 把这个操作数作为有类型的变量打印
        void WriteAsOperand(const Value *V);

        /// 以函数为单位打印UseLists
        void printUseLists(const Function *F);
    };

    void AssemblyWriter::printUseLists(const Function *F) {
        
    }

    void AssemblyWriter::printType(const Type* Ty) {
        Ty->print();
    }

    void AssemblyWriter::WriteAsOperand(const Value *V) {
        if (V->hasName()) {
            // std::cout << "WriteAsOperand: V hasName : " << V->getName() << std::endl;
            PrintName(V);
            return;
        }
        if(cast<Function>(V)){
            // std::cout << "Function needs a name" << std::endl;
        }
        const Constant *CV = cast<Constant>(V);
        if (CV && !(isa<Function>(CV) || isa<GlobalVariable>(CV))) {
            WriteConstant(CV);
            return;
        }
        char Prefix = '%';
        int Slot;
        if (const GlobalVariable *GV = cast<GlobalVariable>(V)) {
            Slot = Machine.getGlobalSlot(GV);
            // std::cout << "---WriteAsOperand: GlobalVariable name, Slot=" << Slot << "---" << std::endl;
            Prefix = '@';
        } else {
            Slot = Machine.getLocalSlot(V);
            // assert(Slot != -1 && "Undefined Local Val");
        }
        if (Slot != -1)
            outfile << Prefix << Slot;
        else
            outfile << "<badref>";
    }

    void AssemblyWriter::WriteConstant(const Constant *CV) {
        if (const ConstantInt *CI = cast<ConstantInt>(CV)) {
            if (CI->getBitWidth() == 1) {
                outfile << (CI->isZero() ? "false" : "true");
            } else {
                outfile << CI->getValue();
            }
            return;
        }
        if (isa<ConstantAggregateZero>(CV)) {
            outfile << "zeroinitializer";
            return;
        }
        if (const ConstantArray *CA = cast<ConstantArray>(CV)) {
            Type *ETy = CA->getType()->getElementType();
            outfile << '[';
            ETy->print();
            outfile << ' ';
            WriteAsOperand(CA->Op<0>());
            for (unsigned i = 1, e = CA->getNumOperands(); i != e; ++i) {
                outfile << ", ";
                ETy->print();
                outfile << ' ';
                WriteAsOperand(CA->getNumOperand(i));
            }
            outfile << ']';
            return;
        }
    }

    void AssemblyWriter::printArgument(const Argument *Arg) {
        Arg->getType()->print();

        if (Arg->hasName()) {
            outfile << ' ';
            PrintName(Arg);
        }
    }

    void AssemblyWriter::writeOperand(const Value *Operand, bool PrintType) {
        assert(Operand && "Operand to be printed is NULLPTR");
        if (PrintType) {
            Operand->getType()->print();
            outfile << ' ';
        }

        WriteAsOperand(Operand);
    }

    void AssemblyWriter::writeParamOperand(const Value *Operand ) {
        if (!Operand) {
            outfile << "<null operand!>";
            return;
        }
        
        Operand->getType()->print();
        outfile << ' ';
        // Print the operand
        WriteAsOperand(Operand);
    }

    void AssemblyWriter::printInstruction(const Instruction* I) {
        outfile << "  ";
        // std::cout << "printInstruction:" << std::endl;
        // 如果有名字就打印名字
        if (I->hasName()) {
            PrintName(I);
            outfile << " = ";
        } else if (!I->getType()->isVoidTy()) {
            int SlotNum = Machine.getLocalSlot(I);
            if (SlotNum == -1)
                outfile << "<badref> = ";
            else
                outfile << '%' << SlotNum << " = ";
            // std::cout << "printInstruction: Inst is not voidTy, SlotNum = " << SlotNum << std::endl;
        }

        /// 打印instruction的操作
        outfile << I->getOpcodeName();
        // std::cout << "printInstruction: Opcode = " << I->getOpcodeName() << std::endl;

        /// 如果是比较指令，打印比较的类型
        if (const ICmpInst *CI = cast<ICmpInst>(I))
            outfile << ' ' << CI->getCmpType();

        // Print out the type of the operands...
        const Value* Operand = I->getNumOperands() ? I->getNumOperand(0) : static_cast<Value*>(nullptr);

        // 如果是condition Branch指令
        if (isa<BranchInst>(I) && cast<BranchInst>(I)->isConditional()) {
            const BranchInst &BI(*cast<BranchInst>(I));
            outfile << ' ';
            writeOperand(BI.Op<0>(), true);
            outfile << ", ";
            writeOperand(BI.Op<2>(), true);
            outfile << ", ";
            writeOperand(BI.Op<1>(), true);

        } else if (const PHINode *PN = cast<PHINode>(I)) {
            outfile << ' ';
            I->getType()->print();
            outfile << ' ';

            for (unsigned op = 0, Eop = PN->getNumIncomingValues(); op < Eop; ++op) {
                if (op) outfile << ", ";
                outfile << "[ ";
                writeOperand(PN->getIncomingValue(op), false); outfile << ", ";
                writeOperand(PN->getIncomingBlock(op), false); outfile << " ]";
            }
        } else if (isa<ReturnInst>(I) && !Operand) {
            outfile << " void";
        } else if (const CallInst *CI = cast<CallInst>(I)) {
            Operand = CI->getCalledValue();
            FunctionType *FTy = CI->getFunctionType();
            Type *RetTy = FTy->getReturnType();
            outfile << ' ';
            if (FTy->isVarArg())
                FTy->print();
            else
                RetTy->print();
            outfile << ' ';
            writeOperand(Operand, false);
            outfile << '(';
            for (unsigned op = 0, Eop = CI->getNumOperands(); op < Eop - 1; ++op) {
                if (op > 0)
                    outfile << ", ";
                writeParamOperand(CI->getNumOperand(op));
            }

            outfile << ')';
        } else if (const AllocaInst *AI = cast<AllocaInst>(I)) {
            // std::cout << "printInstruction: Inst is an AllocaInst" << std::endl;
            outfile << ' ';
            AI->getAllocatedType()->print();
            if (AI->isArrayAllocated()) {
                outfile << ", ";
                writeOperand(AI->getArraySize(), true);
            }
        } else if (Operand) { // Print the normal way.
            if (const auto *GEP = cast<GetElementPtrInst>(I)) {
                outfile << ' ';
                GEP->getSourceElementType()->print();
                outfile << ',';
            } else if (const auto *LI = cast<LoadInst>(I)) {
                outfile << ' ';
                LI->getType()->print();
                outfile << ',';
            }

            bool PrintAllTypes = false;
            Type *TheType = Operand->getType();

            if (isa<StoreInst>(I) || isa<ReturnInst>(I)) {
                PrintAllTypes = true;
            } else {
                for (unsigned i = 1, E = I->getNumOperands(); i != E; ++i) {
                    Operand = I->getNumOperand(i);
                    if (Operand && Operand->getType() != TheType) {
                        PrintAllTypes = true; 
                        break;
                    }
                }
            }

            if (!PrintAllTypes) {
                outfile << ' ';
                TheType->print();
            }

            outfile << ' ';
            for (unsigned i = 0, E = I->getNumOperands(); i != E; ++i) {
                if (i)
                    outfile << ", ";
                writeOperand(I->getNumOperand(i), PrintAllTypes);
            }
        }
    }


    void AssemblyWriter::printInstructionLine(const Instruction *I) {
        printInstruction(I);
        outfile << '\n';
    }

    void AssemblyWriter::printBasicBlock(const BasicBlock *BB) {
        assert(BB && "BB is NULLPTR");
        bool IsEntryBlock = BB == BB->getParent()->getEntryBlock();
        assert(BB->hasName() && "BasicBlock doesn't have its name");
        if (BB->hasName()) { // Print out the label if it exists...
            // std::cout << "printBasicBlock: BB hasName = " << BB->getName() << std::endl;
            outfile << std::endl;
            PrintName(BB->getName(), LabelPrefix);
            outfile << ':';
        } 
        // std::cout << "printBasicBlock: printName end" << std::endl;
        if (!BB->getParent()) {
            outfile << std::endl;
            outfile << "; Error: Block without parent!";
        } 

        outfile << "\n";

        /// 打印这个BB中的所有的指令
        for (auto it = BB->begin(); it != BB->end(); it++) {
            // std::cout << "Instructions" << std::endl;
            printInstructionLine(*it);
        }
    }

    void AssemblyWriter::printFunction(const Function* F) {
        outfile << '\n';

        /// 如果是声明，就去打印declare
        if (F->isDeclaration()) {
            outfile << "declare ";
        }
        else
            outfile << "define ";

        FunctionType* FT = F->getFunctionType();
        F->getReturnType()->print();
        outfile << ' ';
        WriteAsOperand(F);
        outfile << '(';

        // 打印参数
        if (F->isDeclaration()) {
            // std::cout << "printFunction: printing params with declared function" << std::endl;
            for (unsigned I = 0, E = FT->getNumParams(); I != E; ++I) {
                // Insert commas as we go... the first arg doesn't get a comma
                if (I)
                    outfile<< ", ";
                FT->getParamType(I)->print();
            }
        }
        else {
            // std::cout << "printFunction: printing params with defined function" << std::endl;
            // std::cout << "--Arg_size(): " << F->Arg_size() << std::endl;
            for (auto it = F->Arg_begin(); it != F->Arg_end(); it++) {
                // std::cout << "--getArgNo: " << (*it)->getArgNo() << std::endl;
                if ((*it)->getArgNo() != 0)
                    outfile << ", ";
                printArgument(*it);
            }
        }

        /// 打印变参函数的参数
        if (FT->isVarArg()) {
            if (FT->getNumParams()) outfile << ", ";
            outfile << "...";  
        }
        outfile << ')';

        if (F->isDeclaration()) {
            outfile << std::endl;
        }
        else {
            outfile << " {";
            for (auto it = F->BB_begin(); it != F->BB_end(); it++) {
                // std::cout << "printFuncion: BasicBlock" << std::endl;
                printBasicBlock(*it);
            }
            outfile << "}\n";
        }
    }

    void AssemblyWriter::printModule(const YAL::Module *M){
        outfile << "; ModuleID = '" << M->getID() << "'"<<std::endl;
        outfile << "source_filename  = \"" << M->getID() << "\"" << std::endl;
        // 打印所有的global值
        if (!M->global_empty()) outfile << '\n';
        for (const GlobalVariable* GV : M->globals()) {
            printGlobal(GV); 
            outfile << '\n';
        }

        // 打印所有的函数
        for (const Function* F : M->getFunctionList()){
            Machine.setFunction(F);
            printFunction(F);
        }
    }

    void AssemblyWriter::printGlobal(const GlobalVariable *GV){

        /// 打印@GV变量的名字
        WriteAsOperand(GV);
        outfile << " = ";

        /// 是否是变量
        /// GV需要存在isConstant方法
        outfile << (GV->isConstant() ? "constant " : "global ");

        // TODO
        /// print @field = global [2 x i32] zeroinitializer
        GV->getValueType()->print();

        if (GV->hasInitializer()) {
            outfile << ' ';
            writeOperand(GV->getInitializer(), false);
        }
    }
}

/// 以module为入口打印
/// 接下来可能还需要陆续实现以不同的类为入口的打印
void YAL::Module::print(std::string target_name) const {
    SlotTracker SlotTable(this);
    AssemblyWriter W(SlotTable, this);
    writeLog(target_name);
    W.printModule(this);
    closeLog();
}

void YAL::Value::print() const {
    
}

void Type::print() const {
  switch (getTypeID()) {
    case VoidTyID:  {    outfile << "void"; return;}
    case LabelTyID:  {   outfile << "label"; return;}
    case IntegerTyID:{
        auto casted_Ty = cast<IntegerType>(this);
        assert(casted_Ty && "Ty is not IntegerType");
        outfile << 'i' << casted_Ty->getBitWidth();
        return;
    }
    case FunctionTyID: {
        FunctionType* FTy = cast<FunctionType>(this);
        FTy->getReturnType()->print();
        outfile << " (";
        int number = FTy->getNumParams();
        for (int i = 0; i < number; i++) {
            if (i)
                outfile << ", ";
            FTy->getParamType(i)->print();
        }
        if (FTy->isVarArg()) {
            if (FTy->getNumParams()) outfile << ", ";
            outfile << "...";
        }
        outfile << ')';
        return;
    }
    case PointerTyID: {
        PointerType* PTy = cast<PointerType>(this);
        PTy->getElementType()->print();
        outfile << '*';
        return;
    }
    case ArrayTyID: {
        ArrayType *ATy = cast<ArrayType>(this);
        outfile << '[' << ATy->getElementNum() << " x ";
        // std::cout << '[' << ATy->getElementNum() << " x " << std::endl;
        ATy->getElementType()->print();
        outfile << ']';
        // std::cout << ']' << std::endl;
        return;
    }
    default:
        return;
  }
}