
#ifndef _C1_SYNTAX_TREE_H_
#define _C1_SYNTAX_TREE_H_

#include <vector>
#include <memory>
#include <string>
#include<iostream>

namespace c1_recognizer
{
namespace syntax_tree
{
// Use unique postd::stringtype to reference stored objects
template <typename T>
using ptr = std::shared_ptr<T>;

// List of reference of type
template <typename T>
using ptr_list = std::vector<ptr<T>>;

// Enumerations
enum class relop
{
    equal = 0,
    non_equal,
    less,
    less_equal,
    greater,
    greater_equal
};

enum class binop
{
    plus = 0,
    minus,
    multiply,
    divide,
    modulo
};

enum class unaryop
{
    plus = 0,
    minus,
    exclamatory
};

// Forward declaration
struct syntax_tree_node;
struct assembly;

struct global_def_syntax;
struct const_def_stmt_syntax; // 常量定义
struct var_def_stmt_syntax;     //变量定义
struct init_var_syntax; // 初始化数据结构
struct init_const_syntax;

// components of functions
struct func_def_syntax;  //函数定义
struct func_def_param_syntax; // 函数调用传参

// statement sentences
struct stmt_syntax;         //语句
struct assign_stmt_syntax;      //赋值语句
struct expr_stmt_syntax;   // 表达式语句
struct block_syntax;        //{}包围的语句块
struct if_stmt_syntax;      //条件语句
struct while_stmt_syntax;   //while循环语句

// expression sentences
struct const_expr_syntax;
struct expr_syntax;     //表达式
struct add_expr_syntax; // 加减法表达式
struct addop_expr_syntax; // 非虚类加减法
struct mul_expr_syntax; // 乘除模表达式
struct mulop_expr_syntax; // 非虚类乘除法
struct unary_expr_syntax; // 一元表达式
struct func_call_expr_syntax; // 函数调用表达式
struct unaryop_expr_syntax; //（+|-）Exp
struct primary_expr_syntax; // 基本表达式
struct internal_expr_syntax; // （exp）表达式
struct literal_syntax;  //数字
struct lval_syntax;     //标识符([exp])?

// conditional sentences
struct cond_syntax;     //判断语句
struct lor_expr_syntax; // LOr 判断语句
struct lorop_expr_syntax;
struct land_expr_syntax; // LAnd
struct landop_expr_syntax;
struct eq_expr_syntax;
struct eqop_expr_syntax;
struct  rel_expr_syntax;

struct syntax_tree_visitor;

// Virtual base of all kinds of syntax tree nodes.
struct syntax_tree_node
{
    int line;
    int pos;
    // Used in syntax_tree_visitor. Irrelevant to syntax tree generation.
    virtual void accept(syntax_tree_visitor &visitor) = 0;
};

// Root node of an ordinary syntax tree.
struct assembly : syntax_tree_node
{
    ptr_list<global_def_syntax> global_defs;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// Virtual base of lobal definitions, function or variable one.
struct global_def_syntax : virtual syntax_tree_node
{
    virtual void accept(syntax_tree_visitor &visitor) override = 0;
};

// Function definition.
struct func_def_syntax : global_def_syntax
{
    bool is_int;
    std::string name;
    ptr<block_syntax> body;
    ptr_list<func_def_param_syntax> params;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

struct func_def_param_syntax : syntax_tree_node
{
    bool is_Array;
    std::string name;
    ptr_list<expr_syntax> len_array;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

struct cond_syntax : virtual syntax_tree_node
{
    virtual void accept(syntax_tree_visitor &visitor) = 0;
};

struct lor_expr_syntax : virtual cond_syntax
{
     virtual void accept(syntax_tree_visitor &visitor) = 0;
};

struct lorop_expr_syntax : lor_expr_syntax
{
    ptr<lor_expr_syntax> lor_expr;
    ptr<land_expr_syntax> land_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

struct land_expr_syntax : virtual lor_expr_syntax
{
     virtual void accept(syntax_tree_visitor &visitor) = 0;
};

struct landop_expr_syntax : land_expr_syntax
{
    ptr<eq_expr_syntax> eq_expr;
    ptr<land_expr_syntax> land_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

struct eq_expr_syntax : virtual land_expr_syntax
{
    virtual void accept(syntax_tree_visitor &visitor) = 0;
};

struct expr_syntax :  syntax_tree_node
{
    ptr<add_expr_syntax> add_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

struct const_expr_syntax :  syntax_tree_node
{
    ptr<add_expr_syntax> add_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

struct rel_expr_syntax :  eq_expr_syntax
{
    relop op;
    ptr<rel_expr_syntax> rel_expr;
    ptr<add_expr_syntax> add_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// add or minus expression
struct add_expr_syntax : virtual syntax_tree_node
{
    virtual void accept(syntax_tree_visitor &visitor)=0;
};

struct addop_expr_syntax : add_expr_syntax
{
    binop op;
    ptr<add_expr_syntax> add_expr;
    ptr<mul_expr_syntax> mul_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// mul or divide or modulo expression
struct mul_expr_syntax : virtual add_expr_syntax
{
    virtual void accept(syntax_tree_visitor &visitor) = 0;
};

struct mulop_expr_syntax : mul_expr_syntax
{
    binop op;
    ptr<unary_expr_syntax> unary_expr;
    ptr<mul_expr_syntax> mul_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// unary expr 
struct unary_expr_syntax : virtual mul_expr_syntax
{
    virtual void accept(syntax_tree_visitor &visitor) =0;
};

struct unaryop_expr_syntax : unary_expr_syntax
{
    unaryop op;
    ptr<unary_expr_syntax> unary_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final; 
};

struct primary_expr_syntax : virtual unary_expr_syntax
{
    virtual void accept(syntax_tree_visitor &visitor) = 0;
};

struct internal_expr_syntax : primary_expr_syntax
{
    ptr<expr_syntax> internal_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

struct func_call_expr_syntax : unary_expr_syntax
{
    std::string func_name;
    ptr_list<expr_syntax> func_call_params;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// Expression like `ident` or `ident[exp]`.
struct lval_syntax : primary_expr_syntax
{
    std::string name;
    ptr_list<expr_syntax> array_index; // empty if not array
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// Expression constructed by a literal number.
struct literal_syntax : primary_expr_syntax
{
    int intConst;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// Virtual base for statements.
struct stmt_syntax : virtual syntax_tree_node
{
    virtual void accept(syntax_tree_visitor &visitor) = 0;
};

struct eqop_expr_syntax : eq_expr_syntax
{
    relop op;
    ptr<eq_expr_syntax> eq_expr;
    ptr<rel_expr_syntax> rel_expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// struct relop_expr_syntax : rel_expr_syntax
// {
//     relop op;
//     ptr<rel_expr_syntax> rel_expr;
//     ptr<add_expr_syntax> add_expr;
//     virtual void accept(syntax_tree_visitor &visitor) override final;
// };

struct const_def_stmt_syntax : stmt_syntax, global_def_syntax
{
    std::string name;
    ptr_list<const_expr_syntax> array_length; // nullptr for non-array variables 
    ptr<init_const_syntax> initializers;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

struct init_const_syntax : syntax_tree_node
{
    ptr<const_expr_syntax> single_init;
    ptr_list<init_const_syntax> array_init;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// Variable definition. Multiple of this would be both a statement and a global definition; however, itself only
// represents a single variable definition.
struct var_def_stmt_syntax : stmt_syntax, global_def_syntax
{
    std::string name;
    ptr_list<const_expr_syntax> array_length; // nullptr for non-array variables 
    ptr<init_var_syntax> initializers;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

struct init_var_syntax : syntax_tree_node
{
    ptr<expr_syntax> single_init;
    ptr_list<init_var_syntax> array_init;
    virtual void accept(syntax_tree_visitor &visitor) override final;
} ;

// Assignment statement.
struct assign_stmt_syntax : stmt_syntax
{
    ptr<lval_syntax> target;
    ptr<expr_syntax> value;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// expression statement.
struct expr_stmt_syntax : stmt_syntax
{
    ptr<expr_syntax> expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// break statement
struct break_stmt_syntax : stmt_syntax
{
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// return statement
struct return_stmt_syntax : stmt_syntax
{
    ptr<expr_syntax> expr;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// continue statement
struct continue_stmt_syntax : stmt_syntax
{
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// Block statement.
struct block_syntax : stmt_syntax
{
    ptr_list<stmt_syntax> body;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// If statement.
struct if_stmt_syntax : stmt_syntax
{
    ptr<cond_syntax> pred;
    ptr<stmt_syntax> then_body;
    ptr<stmt_syntax> else_body;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// While statement.
struct while_stmt_syntax : stmt_syntax
{
    ptr<cond_syntax> pred;
    ptr<stmt_syntax> body;
    virtual void accept(syntax_tree_visitor &visitor) override final;
};

// Visitor base type
class syntax_tree_visitor
{
public:
    virtual void visit(assembly &node) = 0;
    virtual void visit(const_def_stmt_syntax &node) = 0;
    virtual void visit(var_def_stmt_syntax &node) = 0;
    virtual void visit(init_var_syntax &node) = 0;
    virtual void visit(init_const_syntax &node) = 0;
    virtual void visit(func_def_syntax &node) = 0;
    virtual void visit(func_def_param_syntax &node) = 0;
    virtual void visit(assign_stmt_syntax &node) = 0;
    virtual void visit(expr_stmt_syntax &node)=0;
    virtual void visit(block_syntax &node)=0;
    virtual void visit(if_stmt_syntax &node)=0;
    virtual void visit(while_stmt_syntax &node)=0;
    virtual void visit(break_stmt_syntax &node) = 0;
    virtual void visit(continue_stmt_syntax &node)=0;
    virtual void visit(return_stmt_syntax &node)=0;
    virtual void visit(expr_syntax &node)=0;
    virtual void visit(const_expr_syntax &node)=0;
    virtual void visit(addop_expr_syntax &node)=0;
    virtual void visit(mulop_expr_syntax &node)= 0;
    virtual void visit(unaryop_expr_syntax &node) = 0;
    virtual void visit(internal_expr_syntax &node)=0;
    virtual void visit(lval_syntax &node)=0;
    virtual void visit(literal_syntax &node)=0;
    virtual void visit(func_call_expr_syntax &node)=0;
    virtual void visit(lorop_expr_syntax &node)=0;
    virtual void visit(landop_expr_syntax &node)=0;
    virtual void visit(eqop_expr_syntax &node)= 0;
    virtual void visit(rel_expr_syntax &node)=0;
};
} // end namespace syntax_tree
} // end namespace c1_recognizer

#endif
