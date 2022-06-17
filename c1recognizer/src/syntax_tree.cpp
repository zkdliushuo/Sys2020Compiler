
#include <c1recognizer/syntax_tree.h>

using namespace c1_recognizer::syntax_tree;

void assembly::accept(syntax_tree_visitor &visitor) { visitor.visit(*this); }
void func_def_syntax::accept(syntax_tree_visitor &visitor) { visitor.visit(*this); }
void func_def_param_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void const_expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void addop_expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void mulop_expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void unaryop_expr_syntax::accept(syntax_tree_visitor &visitor) { visitor.visit(*this); }
void internal_expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void func_call_expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void lval_syntax::accept(syntax_tree_visitor &visitor) { visitor.visit(*this); }
void literal_syntax::accept(syntax_tree_visitor &visitor) { visitor.visit(*this); }
void lorop_expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void landop_expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void eqop_expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void rel_expr_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void const_def_stmt_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void init_const_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void var_def_stmt_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void init_var_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void assign_stmt_syntax::accept(syntax_tree_visitor &visitor) { visitor.visit(*this); }
void expr_stmt_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void break_stmt_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void return_stmt_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void continue_stmt_syntax::accept(syntax_tree_visitor &visitor){visitor.visit(*this);}
void block_syntax::accept(syntax_tree_visitor &visitor) { visitor.visit(*this); }
void if_stmt_syntax::accept(syntax_tree_visitor &visitor) { visitor.visit(*this); }
void while_stmt_syntax::accept(syntax_tree_visitor &visitor) { visitor.visit(*this); }

// void assembly::accept(syntax_tree_visitor &visitor) {
//     std::cout<<"Enter assembly"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave assembly"<<std::endl;
// }
// void func_def_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter func_def"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave func_def"<<std::endl;
// }
// void func_def_param_syntax::accept(syntax_tree_visitor &visitor){
//     visitor.visit(*this); 
// }
// void const_expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter const_expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave const_expr"<<std::endl;
// }
// void expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave expr"<<std::endl;
// }
// void addop_expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter addop_expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave addop_expr"<<std::endl;
// }
// void mulop_expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter mulop_expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave mulop_expr"<<std::endl;
// }
// void unaryop_expr_syntax::accept(syntax_tree_visitor &visitor) {
//     std::cout<<"Enter unaryop_expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave unaryop_expr"<<std::endl;
// }
// void internal_expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter internel_expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave internel_expr"<<std::endl;
// }
// void func_call_expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter func_call"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave func_call"<<std::endl;
// }
// void lval_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter lval"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave lval"<<std::endl;
// }
// void literal_syntax::accept(syntax_tree_visitor &visitor) {
//     std::cout<<"Enter literal"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave literal"<<std::endl;
// }
// void lorop_expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter lorop_expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave lorop_expr"<<std::endl;
// }
// void landop_expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter landop_expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave landop_expr"<<std::endl;
// }
// void eqop_expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter eqop_expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave eqop_expr"<<std::endl;
// }
// void rel_expr_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter rel_expr"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave rel_expr"<<std::endl;
// }
// void const_def_stmt_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter const_def"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave const_def"<<std::endl;
// }
// void init_const_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter init_const"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave init_const"<<std::endl;
// }
// void var_def_stmt_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter var_def"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave var_def"<<std::endl;
// }
// void init_var_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter init_var"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave init_var"<<std::endl;
// }
// void assign_stmt_syntax::accept(syntax_tree_visitor &visitor) {
//     std::cout<<"Enter assign_stmt"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave assign_stmt"<<std::endl;
// }
// void expr_stmt_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter expr_stmt"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave expr_stmt"<<std::endl;
// }
// void break_stmt_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter break_stmt"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave break_stmt"<<std::endl;
// }
// void return_stmt_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter return_stmt"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave return_stmt"<<std::endl;
// }
// void continue_stmt_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter continue_stmt"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave continue_stmt"<<std::endl;
// }
// void block_syntax::accept(syntax_tree_visitor &visitor){
//     std::cout<<"Enter block_stmt"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave block_stmt"<<std::endl;
// }
// void if_stmt_syntax::accept(syntax_tree_visitor &visitor) {
//     std::cout<<"Enter if_stmt"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave if_stmt"<<std::endl;
// }
// void while_stmt_syntax::accept(syntax_tree_visitor &visitor) {
//     std::cout<<"Enter while_stmt"<<std::endl;
//     visitor.visit(*this); 
//     std::cout<<"Leave while_stmt"<<std::endl;
// }
