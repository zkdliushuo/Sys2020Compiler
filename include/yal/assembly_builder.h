
#ifndef _C1_ASSEMBLY_BUILDER_H_
#define _C1_ASSEMBLY_BUILDER_H_

#include <deque>
#include <unordered_map>
#include <string>
#include <tuple>

#include "BasicBlock.h"
#include "Constants.h"
#include "Function.h"
#include "IRBuilder.h"
#include "LLVMContext.h"
#include "Module.h"
#include "Type.h"
#include "Instructions.h"

#include "error_reporter.h"
#include "syntax_tree.h"

#include "runtime.h"


class BlockScope
{
public:
    YAL::BasicBlock* while_body,*while_next;
    // 数组变量的各个维度
    std::unordered_map<std::string, std::vector<YAL::Value*>> arraySizes_var;
    std::unordered_map<std::string, std::vector<int>> arraySizes_const;
    std::unordered_map<std::string, std::vector<int>> const_local_init;
    // 变量的指针值，是不是常量，是不是数组
    std::unordered_map<std::string, std::tuple<YAL::Value *, bool, bool>> locals;
};

class WhileScope
{
public:
    YAL::BasicBlock* while_body,*while_next;
};


class assembly_builder : public c1_recognizer::syntax_tree::syntax_tree_visitor
{
    virtual void visit(c1_recognizer::syntax_tree::assembly &node) override;
    virtual void visit(c1_recognizer::syntax_tree::const_def_stmt_syntax &node) override;
    virtual void visit(c1_recognizer::syntax_tree::var_def_stmt_syntax &node) override;
    virtual void visit(c1_recognizer::syntax_tree::init_var_syntax &node) override;
    virtual void visit(c1_recognizer::syntax_tree::init_const_syntax &node) override;
    virtual void visit(c1_recognizer::syntax_tree::func_def_syntax &node) override;
    virtual void visit(c1_recognizer::syntax_tree::func_def_param_syntax &node) override;
    virtual void visit(c1_recognizer::syntax_tree::assign_stmt_syntax &node) override;
    virtual void visit(c1_recognizer::syntax_tree::expr_stmt_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::block_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::if_stmt_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::while_stmt_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::break_stmt_syntax &node) override;
    virtual void visit(c1_recognizer::syntax_tree::continue_stmt_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::return_stmt_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::expr_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::const_expr_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::addop_expr_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::mulop_expr_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::unaryop_expr_syntax &node) override;
    virtual void visit(c1_recognizer::syntax_tree::internal_expr_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::lval_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::literal_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::func_call_expr_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::lorop_expr_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::landop_expr_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::eqop_expr_syntax &node)override;
    virtual void visit(c1_recognizer::syntax_tree::rel_expr_syntax &node)override;

    YAL::LLVMContext &context;
    YAL::IRBuilder builder;
    std::unique_ptr<YAL::Module> module;
    std::unique_ptr<runtime_info> runtime;

    YAL::BasicBlock *cond_then_bb;
    YAL::BasicBlock *cond_else_bb;
    bool Icmp_expected;

    YAL::Value *value_result;
    int int_const_result;

    std::vector<int> ArrayLength;
    std::vector<int> ConstArrayInitVec;
    std::vector<YAL::Value*> VarArrayInitVec;
    int array_init_depth;
    bool in_funcRParam;

    YAL::Function *current_function;
    int bb_count;

    bool lval_as_rval;
    bool in_global;
    bool constexpr_expected;

    c1_recognizer::error_reporter &err;
    bool error_flag;

    // bool in_while_blocks = false;
    // BasicBlock* in_while_block;
    // BasicBlock* in_while_next;

  public:
    assembly_builder(YAL::LLVMContext &ctx, c1_recognizer::error_reporter &error_stream)
        : context(ctx), builder(ctx), err(error_stream) {ArrayLength.resize(0);}

    void build(std::string name, std::shared_ptr<c1_recognizer::syntax_tree::syntax_tree_node> tree)
    {
        // Initialize environment.
        // std::cout<<"Enter IR Builder && Start Building"<<std::endl;
        module = std::make_unique<YAL::Module>(name, context);
        runtime = std::make_unique<runtime_info>(module.get());

        enter_scope();
        // PrintSymbolTable();
        for (auto t : runtime->get_language_symbols())
        {
            YAL::Function *val;
            std::string name;
            std::tie(name, val) = t;
            functions[name] = val;
        }

        lval_as_rval = true;
        in_global = true;
        constexpr_expected = false;
        error_flag = false;
        // Start building by starting iterate over the syntax tree.
        tree->accept(*this);
        // Finish by clear IRBuilder's insertion point and moving away built module.
        builder.ClearInsertionPoint();
        exit_scope();
        if (error_flag)
        {
            module.release();
            runtime.release();
        }
    }

    void PrintSymbolTable(){
        std::cout<<"************************"<< "Function Vector:" << "************************"<<std::endl;
        for(auto m : functions){
            std::cout<<m.first<<std::endl;
        }
        std::cout<<"****************************************************************\n"<<std::endl;
        std::cout<<"**************************"<< "Block Stack:" << "**************************"<<std::endl;
        for(auto m: BlockStack){
            std::cout<<"<===============================>"<<std::endl<<"Local Variable Table:"<<std::endl;
            for(auto each: m->locals){
                std::cout<<each.first <<"\t|\t";
                auto second_tuple = each.second;
                if(std::get<1>(second_tuple)){
                    std::cout<<"Const\t|\t";
                }
                else{
                    std::cout<<"Var\t|\t";
                }
                if(std::get<2>(second_tuple)){
                    std::cout<<"Array\t"<<std::endl;
                }
                else{
                    std::cout<<"Single\t"<<std::endl;
                }
            }
            std::cout <<"Defined Array Size Info Table (Not param-transferred array):"<<std::endl;
            for(auto each: m->arraySizes_const){
                std::cout<<each.first;
                auto second_vec = each.second;
                for(auto every: second_vec){
                    std::cout << "["<<every<<"]";
                }
                std::cout<<std::endl;
            }
            std::cout <<"Const Array Initilizer Info Table:"<<std::endl;
            for(auto each: m->const_local_init){
                std::cout<<each.first;
                auto second_vec = each.second;
                std::cout << "{";
                for(auto every: second_vec){
                    std::cout <<every<<" , ";
                }
                std::cout << "}"<<std::endl;
            }
            std::cout<<"<===============================>"<<std::endl;
        }
        std::cout<<"****************************************************************\n"<<std::endl;
    }

    std::unique_ptr<YAL::Module> get_module() { return std::move(module); }
    std::unique_ptr<runtime_info> get_runtime_info() { return std::move(runtime); }

    YAL::Value* getSymbolValue(std::string name) const{
        for(auto m : BlockStack){
            if(m->locals.count(name)){
                return std::get<0>(m->locals[name]);
            }
        }
        return nullptr;
    }

  private:
    void enter_scope() { 
        // std::cout<<"Enter_Scope Enter"<<std::endl;
        auto temp = new BlockScope();
        BlockStack.emplace_front(temp);
        BlockStack.front()->while_body=nullptr;
        BlockStack.front()->while_next=nullptr;
        // std::cout<<"Enter_Scope Return"<<std::endl;
     }

    void exit_scope() { BlockStack.pop_front(); }

    std::vector<int> CalCurIndex();

    // Value* ,is_const, is_array
    std::tuple<YAL::Value *, bool, bool> lookup_variable(std::string name)
    {
        for (auto m : BlockStack)
            if (m->locals.count(name))
                return m->locals[name];
        return std::make_tuple((YAL::Value *)nullptr, false, false);
    }

    bool declare_variable(std::string name, YAL::Value *var_ptr, bool is_const, bool is_array)
    {
        if(BlockStack.front()->locals.count(name)){
            return false;
        }
        BlockStack.front()->locals[name] = std::make_tuple(var_ptr, is_const, is_array);
        return true;
    }

    bool SetArraySize(std::string name, std::vector<int>length)
    {
        if(std::get<2>(BlockStack.front()->locals[name])){
            if( BlockStack.front()->arraySizes_const.count(name)){
                return false;
            }
            else{
                BlockStack.front()->arraySizes_const[name] = length;
                return true;
            }
        }
        return false;
    }

    bool SetArraySize(std::string name, std::vector<YAL::Value*>length)
    {
        if(std::get<2>(BlockStack.front()->locals[name])){
            if( BlockStack.front()->arraySizes_var.count(name)){
                return false;
            }
            else{
                BlockStack.front()->arraySizes_var[name] = length;
                return true;
            }
        }
        return false;
    }

    bool SetConstInit(std::string name, std::vector<int> InitVec)
    {
        if( BlockStack.front()->const_local_init.count(name)){
            return false;
        }
        else{
            BlockStack.front()->const_local_init[name] = InitVec;
            return true;
        }
    }

    bool SetConstInit(std::string name, int InitInt)
    {
        if(!std::get<2>(BlockStack.front()->locals[name])){
            if( BlockStack.front()->const_local_init.count(name)){
                return false;
            }
            else{
                std::vector<int> temp;
                temp.push_back(InitInt);
                BlockStack.front()->const_local_init[name] = temp;
                return true;
            }
        }
        return false;
    }

    std::vector<int> GetConstInit(std::string name)
    {
        std::vector<int> Nothing;
        for(auto m : BlockStack){
            if(m->const_local_init.count(name)){
                return m->const_local_init[name];
            }
        }
        return Nothing;
    }

    std::tuple<int, std::vector<YAL::Value*>, std::vector<int>> GetArraySize(std::string name)
    {
        std::vector<YAL::Value*> Nothing_var;
        std::vector<int> Nothing_const;
        int which_one=0;
        for(auto m : BlockStack){
            if(m->arraySizes_const.count(name)){
                which_one = 2;
                Nothing_const = m->arraySizes_const[name];
                break;
            }
            else if (m->arraySizes_var.count(name)){
                which_one = 1;
                Nothing_var = m->arraySizes_var[name];
                break;
            }
        }
        return std::make_tuple(which_one,Nothing_var,Nothing_const);
        // if(BlockStack.front()->arraySizes_const.count(name)){
        //     return std::make_tuple(2,Nothing_var,BlockStack.front()->arraySizes_const[name]);
        // }
        // else if(BlockStack.front()->arraySizes_var.count(name)){
        //     return std::make_tuple(1,BlockStack.front()->arraySizes_var[name],Nothing_const);
        // }
        // else{
        //     return std::make_tuple(0,Nothing_var,Nothing_const);
        // }
    }

    std::deque<BlockScope *> BlockStack;
    std::deque<WhileScope *> WhileStack;

    std::unordered_map<std::string, YAL::Function *> functions;

    void SetWhileBlocks(YAL::BasicBlock* body, YAL::BasicBlock* next){
        auto temp = new WhileScope();
        WhileStack.emplace_front(temp);
        WhileStack.front()->while_body = body;
        WhileStack.front()->while_next = next;
    }

    bool SetBreak(){
        for(auto m: WhileStack){
            if(m->while_next){
                builder.CreateBr(m->while_next);
                return true;
            }
        }
        return false;
    }

    bool SetContinue(){
        for(auto m: WhileStack){
            if(m->while_body){
                builder.CreateBr(m->while_body);
                return true;
            }
        }
        return false;
    }

    void LeaveWhieBlocks() { WhileStack.pop_front(); }

    YAL::Value* CastToBoolean(YAL::Value* condValue){
        if( condValue->getType() == YAL::Type::getInt32Ty(context) ){
            return builder.CreateICmpNE(condValue, YAL::ConstantInt::get(context, 0));
        }
        else{
            return condValue;
        }
    }

    YAL::Value* CastToInt32(YAL::Value* condValue){
        if(condValue->getType()==YAL::Type::getInt1Ty(context)){
            return builder.CreateZExt(condValue,YAL::Type::getInt32Ty(context));
        }
        else{
            return condValue;
        }
    }
};

#endif
