
#ifndef _C1_TEST_SYNTAX_TREE_SERIALIZER_
#define _C1_TEST_SYNTAX_TREE_SERIALIZER_

#include <c1recognizer/syntax_tree.h>

namespace c1_recognizer
{
namespace syntax_tree
{

std::string relop_name_map[] = {"equal", "non_equal", "less", "less_equal", "greater", "greater_equal"};
std::string binop_name_map[] = {"plus", "minus", "multiply", "divide", "modulo"};
std::string unaryop_name_map[] = {"plus", "minus"};

template <typename Writer>
class syntax_tree_serializer : public syntax_tree_visitor
{
  public:
    syntax_tree_serializer(Writer &w) : writer(w) {}

    void serialize(syntax_tree_node &tree)
    {
        tree.accept(*this);
    }

    virtual void visit(assembly &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("assembly");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("global_defs");
        writer.StartArray();
        for (auto def : tree.global_defs)
            def->accept(*this);
        writer.EndArray();
        writer.EndObject();
    }

    virtual void visit(const_def_stmt_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("const_def_stmt");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("name");
        writer.String(tree.name.c_str());
        writer.Key("array_length");
        writer.StartArray();
        for(auto len: tree.array_length)
            len->accept(*this);
        writer.EndArray();
        writer.Key("initializers");
        tree.initializers->accept(*this);
        writer.EndObject();
    }

    virtual void visit(var_def_stmt_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("var_def_stmt");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("name");
        writer.String(tree.name.c_str());
        writer.Key("array_length");
        writer.StartArray();
        for(auto len: tree.array_length)
            len->accept(*this);
        writer.EndArray();
        if(tree.initializers){
            writer.Key("initializers");
            tree.initializers->accept(*this);
        }
        writer.EndObject();
    }

    virtual void visit(init_var_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("init_var");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("init_elements");
        if(tree.single_init == nullptr){
            writer.StartArray();
            for(auto len: tree.array_init)
                len->accept(*this);
            writer.EndArray();
        }
        else{
            tree.single_init->accept(*this);
        }
        writer.EndObject();
    }

    virtual void visit(init_const_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("init_const");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("init_elements");
        if(tree.single_init == nullptr){
            writer.StartArray();
            for(auto len: tree.array_init)
                len->accept(*this);
            writer.EndArray();
        }
        else{
            tree.single_init->accept(*this);
        }
        writer.EndObject();
    }

    virtual void visit(func_def_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("func_def_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("func_name");
        writer.String(tree.name.c_str());
        writer.Key("return_value");
        writer.Bool(tree.is_int);
        writer.Key("parameters");
        writer.StartArray();
        for(auto param: tree.params){
            param->accept(*this);
        }
        writer.EndArray();
        writer.Key("body");
        tree.body->accept(*this);
        writer.EndObject();
    }

    virtual void visit(func_def_param_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("func_def_param");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("identifier");
        writer.String(tree.name.c_str());
        writer.Key("IsArray");
        writer.Bool(tree.is_Array);
        writer.Key("array_length");
        writer.StartArray();
        for(auto param: tree.len_array){
            param->accept(*this);
        }
        writer.EndArray();
        writer.EndObject();
    }

    virtual void visit(assign_stmt_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("assign_stmt");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("target");
        tree.target->accept(*this);
        writer.Key("value");
        tree.value->accept(*this);
        writer.EndObject();
    }

    virtual void visit(expr_stmt_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("expr_stmt");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        if(tree.expr){
            writer.Key("expr");
            tree.expr->accept(*this);
        }
        writer.EndObject();
    }

   virtual void visit(block_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("block_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("body");
        writer.StartArray();
        for (auto stmt : tree.body)
            stmt->accept(*this);
        writer.EndArray();
        writer.EndObject();
    }

    virtual void visit(if_stmt_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("if_stmt_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("pred");
        tree.pred->accept(*this);
        writer.Key("thenbody");
        tree.then_body->accept(*this);
        if (tree.else_body)
        {
            writer.Key("elsebody");
            tree.else_body->accept(*this);
        }
        writer.EndObject();
    }

    virtual void visit(while_stmt_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("while_stmt_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("pred");
        tree.pred->accept(*this);
        writer.Key("body");
        tree.body->accept(*this);
        writer.EndObject();
    }

    virtual void visit(break_stmt_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("break_stmt_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.EndObject();
    }

    virtual void visit(continue_stmt_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("continue_stmt_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.EndObject();
    }

    virtual void visit(return_stmt_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("return_stmt_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        if(tree.expr){
            writer.Key("return_value");
            tree.expr->accept(*this);   
        }
        writer.EndObject();
    }

    virtual void visit(expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("add_expr");
        tree.add_expr->accept(*this);
        writer.EndObject();
    }

    virtual void visit(const_expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("const_expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("add_expr");
        tree.add_expr->accept(*this);
        writer.EndObject();
    }

    virtual void visit(addop_expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("addop_expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("op");
        writer.String(binop_name_map[int(tree.op)].c_str());
        writer.Key("add_expr");
        tree.add_expr->accept(*this);
        writer.Key("mul_expr");
        tree.mul_expr->accept(*this);
        writer.EndObject();
    }

    virtual void visit(mulop_expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("mulop_expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("op");
        writer.String(binop_name_map[int(tree.op)].c_str());
        writer.Key("mul_expr");
        tree.mul_expr->accept(*this);
        writer.Key("unaray_expr");
        tree.unary_expr->accept(*this);
        writer.EndObject();
    }

    virtual void visit(unaryop_expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("unaryop_expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("op");
        writer.String(unaryop_name_map[int(tree.op)].c_str());
        writer.Key("unaray_expr");
        tree.unary_expr->accept(*this);
        writer.EndObject();
    }

    virtual void visit(internal_expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("internal_expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("internal_expr");
        tree.internal_expr->accept(*this);
        writer.EndObject();
    }

    virtual void visit(lval_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("lval_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("name");
        writer.String(tree.name.c_str());
        writer.Key("array_index");
        writer.StartArray();
        for (auto index : tree.array_index)
            index->accept(*this);
        writer.EndArray();
        writer.EndObject();
    }

    virtual void visit(literal_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("literal_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("value");
        writer.Int(tree.intConst);
        writer.EndObject();
    }
    
    virtual void visit(func_call_expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("func_call_expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("func_name");
        writer.String(tree.func_name.c_str());
        writer.Key("call_params");
        writer.StartArray();
        for (auto param : tree.func_call_params)
            param->accept(*this);
        writer.EndArray();
        writer.EndObject();
    }

    virtual void visit(lorop_expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("lorop_expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("lor_expr");
        tree.lor_expr->accept(*this);
        writer.Key("land_expr");
        tree.land_expr->accept(*this);
        writer.EndObject();
    }

    virtual void visit(landop_expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("landop_expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("land_expr");
        tree.land_expr->accept(*this);
        writer.Key("eq_expr");
        tree.eq_expr->accept(*this);
        writer.EndObject();
    }

    virtual void visit(eqop_expr_syntax &tree) override
    {
        writer.StartObject();
        writer.Key("type");
        writer.String("eqop_expr_syntax");
        writer.Key("line");
        writer.Int(tree.line);
        writer.Key("pos");
        writer.Int(tree.pos);
        writer.Key("op");
        writer.String(relop_name_map[int(tree.op)].c_str());
        writer.Key("eq_expr");
        tree.eq_expr->accept(*this);
        writer.Key("rel_expr");
        tree.rel_expr->accept(*this);
        writer.EndObject();
    }
    
    virtual void visit(rel_expr_syntax &tree) override
    {
        if(tree.rel_expr){
            writer.StartObject();
            writer.Key("type");
            writer.String("rel_expr_syntax");
            writer.Key("line");
            writer.Int(tree.line);
            writer.Key("pos");
            writer.Int(tree.pos);
            writer.Key("op");
            writer.String(relop_name_map[int(tree.op)].c_str());
            writer.Key("rel_expr");
            tree.rel_expr->accept(*this);
            writer.Key("add_expr");
            tree.add_expr->accept(*this);
            writer.EndObject();
        }
        else
        {
            tree.add_expr->accept(*this);
        }
    }

  private:
    Writer &writer;
};
}
}

#endif
