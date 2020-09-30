#include "syntax_tree_builder.h"
#include <memory>

using namespace c1_recognizer;
using namespace c1_recognizer::syntax_tree;

syntax_tree_builder::syntax_tree_builder(error_reporter &_err) : err(_err) {}

// 父节点使用reset初始化，return result
// 父节点使用智能指针压倒指针列表里，return ptr<T>{result}
// 父节点使用虚类列表 return static_cast<T>(result)
antlrcpp::Any syntax_tree_builder::visitCompilationUnit(C1Parser::CompilationUnitContext *ctx) {
  // std::cout<<"enter compilationunit"<<std::endl;
  auto result = new assembly;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  auto start_items = ctx->start();
  for (auto each : start_items) {
    // std::cout<<each->toString()<<std::endl;
    if (each->funcdef()) {
      //  std::cout<<"before enter funcdef"<<std::endl;
      auto func_def = visit(each->funcdef()).as<ptr<func_def_syntax>>();
      // std::cout<<func_def->name<<std::endl;
      result->global_defs.push_back(func_def);
      continue;
    }
    if (each->decl()->constdecl()) {
      auto decls = visit(each->decl()).as<ptr_list<const_def_stmt_syntax>>();
      for (auto every : decls) {
        result->global_defs.push_back(every);
      }
      continue;
    }
    if (each->decl()->vardecl()) {
      auto decls = visit(each->decl()).as<ptr_list<var_def_stmt_syntax>>();
      //  std::cout<<"vardecl back to assmbly"<<std::endl;
      for (auto every : decls) {
        result->global_defs.push_back(every);
      }
      // std::cout<<"all vardef has been pushed back into the global_defs list"<<std::endl;
      continue;
    }
  }
  // std::cout<<"return assmbly"<<std::endl;
  return result;
}

antlrcpp::Any syntax_tree_builder::visitDecl(C1Parser::DeclContext *ctx) {
  // std::cout<<"enter Decl"<<std::endl;
  if (ctx->constdecl()) {
    return visit(ctx->constdecl());
  } else {
    return visit(ctx->vardecl());
  }
}

antlrcpp::Any syntax_tree_builder::visitConstdecl(C1Parser::ConstdeclContext *ctx) {
  // std::cout<<"enter constdecl"<<std::endl;
  ptr_list<const_def_stmt_syntax> result;
  for (auto each : ctx->constdef()) {
    auto const_def = visit(each).as<ptr<const_def_stmt_syntax>>();
    result.push_back(const_def);
  }
  return result;
}

antlrcpp::Any syntax_tree_builder::visitConstdef(C1Parser::ConstdefContext *ctx) {
  // std::cout<<"enter constdef"<<std::endl;
  auto result = new const_def_stmt_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  result->name = ctx->Identifier()->getSymbol()->getText();
  // 如果这个变量声明不是数组
  if (ctx->LeftBracket().empty()) {
    result->array_length.clear();
    result->initializers.reset(visit(ctx->constinitval()).as<init_const_syntax *>());
  } else {
    for (auto each : ctx->constexp()) {
      result->array_length.push_back(ptr<const_expr_syntax>(visit(each).as<const_expr_syntax *>()));
    }
    result->initializers.reset(visit(ctx->constinitval()).as<init_const_syntax *>());
  }
  return ptr<const_def_stmt_syntax>(result);
}

antlrcpp::Any syntax_tree_builder::visitConstinitval(C1Parser::ConstinitvalContext *ctx) {
  // std::cout<<"enter constinitval"<<std::endl;
  auto result = new init_const_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  result->array_init.clear();
  if (ctx->constexp()) {
    result->single_init.reset(visit(ctx->constexp()).as<const_expr_syntax *>());
    // std::cout<<"back to constinitval"<<std::endl;
  } else {
    result->single_init = nullptr;
    for (auto each : ctx->constinitval()) {
      result->array_init.push_back(ptr<init_const_syntax>(visit(each).as<init_const_syntax *>()));
      // std::cout<<"back to constinitval"<<std::endl;
    }
  }
  return result;
}

antlrcpp::Any syntax_tree_builder::visitVardecl(C1Parser::VardeclContext *ctx) {
  // std::cout<<"enter vardecl"<<std::endl;
  ptr_list<var_def_stmt_syntax> result;
  for (auto each : ctx->vardef()) {
    auto var_def = visit(each).as<ptr<var_def_stmt_syntax>>();
    // std::cout<<"vardef back to vardecl"<<std::endl;
    result.push_back(var_def);
  }
  return result;
}

antlrcpp::Any syntax_tree_builder::visitVardef(C1Parser::VardefContext *ctx) {
  // std::cout<<"enter vardef"<<std::endl;
  auto result = new var_def_stmt_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  result->name = ctx->Identifier()->getSymbol()->getText();
  if (ctx->Assign()) {
    result->initializers.reset(visit(ctx->initval()).as<init_var_syntax *>());
  } else {
    result->initializers = nullptr;
  }
  // std::cout<<"initvar back to vardef"<<std::endl;
  // 如果这个变量声明不是数组
  if (ctx->LeftBracket().empty()) {
    result->array_length.clear();
  } else {
    for (auto each : ctx->constexp()) {
      result->array_length.push_back(ptr<const_expr_syntax>(visit(each).as<const_expr_syntax *>()));
    }
  }
  // std::cout<<"array_len back to vardef"<<std::endl;
  return ptr<var_def_stmt_syntax>(result);
}

antlrcpp::Any syntax_tree_builder::visitInitval(C1Parser::InitvalContext *ctx) {
  // std::cout<<"enter initval"<<std::endl;
  auto result = new init_var_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  result->array_init.clear();
  if (auto exp = ctx->exp()) {
    result->single_init.reset(visit(exp).as<expr_syntax *>());
  } else {
    result->single_init = nullptr;
    for (auto each : ctx->initval()) {
      result->array_init.push_back(ptr<init_var_syntax>(visit(each).as<init_var_syntax *>()));
    }
  }
  // std::cout<< "vardef initval is at " << result->line<<std::endl;
  return result;
}

// funcdef: Void Identifier LeftParen RightParen block;
antlrcpp::Any syntax_tree_builder::visitFuncdef(C1Parser::FuncdefContext *ctx) {
  // std::cout<<"enter funcdef"<<std::endl;
  auto result = new func_def_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  result->name = ctx->Identifier()->getSymbol()->getText();
  if (ctx->functype()->Int()) {
    result->is_int = true;
  } else if (ctx->functype()->Void()) {
    result->is_int = false;
  }
  if (ctx->funcfparams()) {
    for (auto each : ctx->funcfparams()->funcfparam()) {
      result->params.push_back(ptr<func_def_param_syntax>(visit(each).as<func_def_param_syntax *>()));
    }
  } else {
    result->params.clear();
  }
  auto body = visit(ctx->block()).as<block_syntax *>();
  result->body.reset(body);
  return ptr<func_def_syntax>{result};
}

antlrcpp::Any syntax_tree_builder::visitFuncfparam(C1Parser::FuncfparamContext *ctx) {
  // std::cout<<"enter funcfparam"<<std::endl;
  auto result = new func_def_param_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  result->name = ctx->Identifier()->getSymbol()->getText();
  result->len_array.clear();
  if (ctx->LeftBracket().empty())
    result->is_Array = false;
  else
    result->is_Array = true;
  for (auto each : ctx->exp()) {
    // // std::cout<<"enter funcfparam's exp as length"<<std::endl;
    result->len_array.push_back(ptr<expr_syntax>(visit(each).as<expr_syntax *>()));
  }
  return result;
}

// LeftBrace (decl | stmt)* RightBrace;
antlrcpp::Any syntax_tree_builder::visitBlock(C1Parser::BlockContext *ctx) {
  // std::cout<<"enter block"<<std::endl;
  auto result = new block_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  auto block_body = ctx->blockbody();
  for (auto each : block_body) {
    if (each->stmt()) {
      result->body.push_back(ptr<stmt_syntax>(visit(each->stmt()).as<stmt_syntax *>()));
      continue;
    }
    if (each->decl()->constdecl()) {
      auto decls = visit(each->decl()).as<ptr_list<const_def_stmt_syntax>>();
      for (auto every : decls) {
        result->body.push_back(every);
      }
      continue;
    }
    if (each->decl()->vardecl()) {
      auto decls = visit(each->decl()).as<ptr_list<var_def_stmt_syntax>>();
      for (auto every : decls) {
        result->body.push_back(every);
      }
      continue;
    }
  }
  return result;
}

antlrcpp::Any syntax_tree_builder::visitStmt(C1Parser::StmtContext *ctx) {
  // std::cout<<"enter stmt"<<std::endl;
  if (ctx->Assign()) {
    auto result = new assign_stmt_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->target.reset(visit(ctx->lval()).as<lval_syntax *>());
    result->value.reset(visit(ctx->exp()).as<expr_syntax *>());
    return static_cast<stmt_syntax *>(result);
  } else if (ctx->SemiColon()) {
    if (ctx->Break()) {
      auto result = new break_stmt_syntax;
      result->line = ctx->getStart()->getLine();
      result->pos = ctx->getStart()->getCharPositionInLine();
      return static_cast<stmt_syntax *>(result);
    } else if (ctx->Continue()) {
      auto result = new continue_stmt_syntax;
      result->line = ctx->getStart()->getLine();
      result->pos = ctx->getStart()->getCharPositionInLine();
      return static_cast<stmt_syntax *>(result);
    } else if (ctx->Return()) {
      // std::cout<<"enter return stmt"<<std::endl;
      auto result = new return_stmt_syntax;
      result->line = ctx->getStart()->getLine();
      result->pos = ctx->getStart()->getCharPositionInLine();
      result->expr = nullptr;
      if (ctx->exp()) {
        result->expr.reset(visit(ctx->exp()).as<expr_syntax *>());
      }
      return static_cast<stmt_syntax *>(result);
    } else if (ctx->exp()) {
      auto result = new expr_stmt_syntax;
      result->line = ctx->getStart()->getLine();
      result->pos = ctx->getStart()->getCharPositionInLine();
      result->expr.reset(visit(ctx->exp()).as<expr_syntax *>());
      return static_cast<stmt_syntax *>(result);
    }
  } else if (auto block = ctx->block()) {
    auto block_ptr = visit(block).as<block_syntax *>();
    return static_cast<stmt_syntax *>(block_ptr);
  } else if (ctx->If()) {
    auto result = new if_stmt_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->pred.reset(visit(ctx->cond()).as<cond_syntax *>());
    result->then_body.reset(visit(ctx->stmt(0)).as<stmt_syntax *>());
    if (ctx->Else()) {
      result->else_body.reset(visit(ctx->stmt(1)).as<stmt_syntax *>());
    } else {
      result->else_body = nullptr;
    }
    return static_cast<stmt_syntax *>(result);
  } else if (ctx->While()) {
    auto result = new while_stmt_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->pred.reset(visit(ctx->cond()).as<cond_syntax *>());
    result->body.reset(visit(ctx->stmt(0)).as<stmt_syntax *>());
    return static_cast<stmt_syntax *>(result);
  }
}

antlrcpp::Any syntax_tree_builder::visitLval(C1Parser::LvalContext *ctx) {
  // std::cout<<"enter lval"<<std::endl;
  auto result = new lval_syntax;
  auto identifier = ctx->Identifier();
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  result->name = identifier->getSymbol()->getText();
  if (ctx->LeftBracket().empty()) {
    result->array_index.clear();
  } else {
    for (auto each : ctx->exp()) {
      result->array_index.push_back(ptr<expr_syntax>(visit(each).as<expr_syntax *>()));
    }
  }
  return result;
}
// exp (Equal | NonEqual | Less | Greater | LessEqual | GreaterEqual) exp;
antlrcpp::Any syntax_tree_builder::visitCond(C1Parser::CondContext *ctx) {
  // std::cout<<"enter cond"<<std::endl;
  return static_cast<cond_syntax *>(visit(ctx->lorexp()).as<lor_expr_syntax *>());
}

antlrcpp::Any syntax_tree_builder::visitLorexp(C1Parser::LorexpContext *ctx) {
  // std::cout<<"enter lorexp"<<std::endl;
  if (ctx->lorexp()) {
    auto result = new lorop_expr_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->lor_expr.reset(visit(ctx->lorexp()).as<lor_expr_syntax *>());
    result->land_expr.reset(visit(ctx->landexp()).as<land_expr_syntax *>());
    return static_cast<lor_expr_syntax *>(result);
  } else {
    return static_cast<lor_expr_syntax *>(visit(ctx->landexp()).as<land_expr_syntax *>());
  }
}

antlrcpp::Any syntax_tree_builder::visitLandexp(C1Parser::LandexpContext *ctx) {
  // std::cout<<"enter landexp"<<std::endl;
  if (ctx->landexp()) {
    auto result = new landop_expr_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->land_expr.reset(visit(ctx->landexp()).as<land_expr_syntax *>());
    result->eq_expr.reset(visit(ctx->eqexp()).as<eq_expr_syntax *>());
    return static_cast<land_expr_syntax *>(result);
  } else {
    return static_cast<land_expr_syntax *>(visit(ctx->eqexp()).as<eq_expr_syntax *>());
  }
}

antlrcpp::Any syntax_tree_builder::visitEqexp(C1Parser::EqexpContext *ctx) {
  // std::cout<<"enter eqexp"<<std::endl;
  if (ctx->eqexp()) {
    auto result = new eqop_expr_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    if (ctx->Equal()) {
      result->op = relop::equal;
    } else if (ctx->NonEqual()) {
      result->op = relop::non_equal;
    }
    result->eq_expr.reset(visit(ctx->eqexp()).as<eq_expr_syntax *>());
    result->rel_expr.reset(visit(ctx->relexp()).as<rel_expr_syntax *>());
    return static_cast<eq_expr_syntax *>(result);
  } else {
    return static_cast<eq_expr_syntax *>(visit(ctx->relexp()).as<rel_expr_syntax *>());
  }
}

antlrcpp::Any syntax_tree_builder::visitRelexp(C1Parser::RelexpContext *ctx) {
  // std::cout<<"enter relexp"<<std::endl;
  auto result = new rel_expr_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  if (ctx->relexp()) {
    if (ctx->Greater()) {
      result->op = relop::greater;
    } else if (ctx->GreaterEqual()) {
      result->op = relop::greater_equal;
    } else if (ctx->Less()) {
      result->op = relop::less;
    } else if (ctx->LessEqual()) {
      result->op = relop::less_equal;
    }
    result->rel_expr.reset(visit(ctx->relexp()).as<rel_expr_syntax *>());
    result->add_expr.reset(visit(ctx->addexp()).as<add_expr_syntax *>());
    return result;
  } else {
    result->rel_expr = nullptr;
    result->add_expr.reset(visit(ctx->addexp()).as<add_expr_syntax *>());
    return result;
  }
}

antlrcpp::Any syntax_tree_builder::visitConstexp(C1Parser::ConstexpContext *ctx) {
  // std::cout<<"enter constexp"<<std::endl;
  // 之后使用的ident应该是常量 这里是sys语言的超集
  auto result = new const_expr_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  result->add_expr.reset(visit(ctx->addexp()).as<add_expr_syntax *>());
  return result;
}

antlrcpp::Any syntax_tree_builder::visitExp(C1Parser::ExpContext *ctx) {
  // std::cout<<"enter exp"<<std::endl;
  auto result = new expr_syntax;
  result->line = ctx->getStart()->getLine();
  result->pos = ctx->getStart()->getCharPositionInLine();
  result->add_expr.reset(visit(ctx->addexp()).as<add_expr_syntax *>());
  return result;
}

antlrcpp::Any syntax_tree_builder::visitAddexp(C1Parser::AddexpContext *ctx) {
  // std::cout<<"enter addexp"<<std::endl;
  if (auto add_expr = ctx->addexp()) {
    auto result = new addop_expr_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    if (ctx->Plus()) {
      result->op = binop::plus;
    }
    if (ctx->Minus()) {
      result->op = binop::minus;
    }
    result->add_expr.reset(visit(add_expr).as<add_expr_syntax *>());
    result->mul_expr.reset(visit(ctx->mulexp()).as<mul_expr_syntax *>());
    try {
      return static_cast<add_expr_syntax *>(result);
    } catch (const std::exception &e) {
      std::cerr << e.what() << " addop_exp -> add_expr" << '\n';
    }
  } else {
    try {
      auto temp = visit(ctx->mulexp()).as<mul_expr_syntax *>();
      // std::cout<<temp->line<<std::endl;
      return static_cast<add_expr_syntax *>(temp);
    } catch (const std::exception &e) {
      std::cerr << e.what() << " mul_exp -> add_expr" << '\n';
    }
  }
}

antlrcpp::Any syntax_tree_builder::visitMulexp(C1Parser::MulexpContext *ctx) {
  // std::cout<<"enter mulexp"<<std::endl;
  if (auto add_expr = ctx->mulexp()) {
    auto result = new mulop_expr_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    if (ctx->Multiply()) {
      result->op = binop::multiply;
    } else if (ctx->Divide()) {
      result->op = binop::divide;
    } else if (ctx->Modulo()) {
      result->op = binop::modulo;
    }
    result->mul_expr.reset(visit(ctx->mulexp()).as<mul_expr_syntax *>());
    result->unary_expr.reset(visit(ctx->unaryexp()).as<unary_expr_syntax *>());
    try {
      return static_cast<mul_expr_syntax *>(result);
    } catch (const std::exception &e) {
      std::cerr << e.what() << " mulop_exp -> mul_expr" << '\n';
    }
  } else {
    try {
      auto temp = visit(ctx->unaryexp()).as<unary_expr_syntax *>();
      // std::cout<<temp->line<<std::endl;
      return static_cast<mul_expr_syntax *>(temp);
    } catch (const std::exception &e) {
      std::cerr << e.what() << " unary_exp -> mul_expr" << '\n';
    }
  }
}

antlrcpp::Any syntax_tree_builder::visitUnaryexp(C1Parser::UnaryexpContext *ctx) {
  // std::cout<<"enter unaryexp"<<std::endl;
  if (auto primary_exp = ctx->primaryexp()) {
    try {
      auto temp = visit(primary_exp).as<primary_expr_syntax *>();
      // std::cout<<temp->line<<std::endl;
      return static_cast<unary_expr_syntax *>(temp);
    } catch (const std::exception &e) {
      std::cerr << e.what() << " primary_exp -> unary_expr" << '\n';
    }
  } else if (ctx->Identifier()) {
    auto result = new func_call_expr_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    result->func_name = ctx->Identifier()->getSymbol()->getText();
    result->func_call_params.clear();
    if (ctx->funcrparams()) {
      // auto params = visit(ctx->funcrparams()).as<ptr_list<expr_syntax>>();
      for (auto each : ctx->funcrparams()->exp()) {
        try {
          result->func_call_params.push_back(ptr<expr_syntax>(visit(each).as<expr_syntax *>()));
        } catch (const std::exception &e) {
          std::cerr << e.what() << " func_call_param_expr -> unary_expr" << '\n';
        }
      }
    }
    try {
      return static_cast<unary_expr_syntax *>(result);
    } catch (const std::exception &e) {
      std::cerr << e.what() << " func_call -> unary_expr" << '\n';
    }
  } else if (ctx->unaryop()) {
    auto result = new unaryop_expr_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    if (ctx->unaryop()->Plus()) {
      result->op = unaryop::plus;
    } else if (ctx->unaryop()->Minus()) {
      result->op = unaryop::minus;
    } else if (ctx->unaryop()->Negative()) {
      result->op = unaryop::exclamatory;
    }
    try {
      result->unary_expr.reset(visit(ctx->unaryexp()).as<unary_expr_syntax *>());
    } catch (const std::exception &e) {
      std::cerr << e.what() << " unary_expr -> unary_expr" << '\n';
    }
    try {
      return static_cast<unary_expr_syntax *>(result);
    } catch (const std::exception &e) {
      std::cerr << e.what() << " unaryop_expr -> unary_expr" << '\n';
    }
  }
}

antlrcpp::Any syntax_tree_builder::visitPrimaryexp(C1Parser::PrimaryexpContext *ctx) {
  // std::cout<<"enter primaryexp"<<std::endl;
  if (ctx->LeftParen()) {
    auto result = new internal_expr_syntax;
    result->line = ctx->getStart()->getLine();
    result->pos = ctx->getStart()->getCharPositionInLine();
    try {
      result->internal_expr.reset(visit(ctx->exp()).as<expr_syntax *>());
    } catch (const std::exception &e) {
      std::cerr << e.what() << " exp -> primary_expr" << '\n';
    }
    try {
      return static_cast<primary_expr_syntax *>(result);
    } catch (const std::exception &e) {
      std::cerr << e.what() << " primary_expr -> primary_expr" << '\n';
    }
  } else if (ctx->lval()) {
    try {
      return static_cast<primary_expr_syntax *>(visit(ctx->lval()).as<lval_syntax *>());
    } catch (const std::exception &e) {
      std::cerr << e.what() << " lval -> primary_expr" << '\n';
    }
  } else if (ctx->number()) {
    try {
      auto temp = visit(ctx->number()).as<literal_syntax *>();
      // std::cout<<temp->intConst<<std::endl;
      return static_cast<primary_expr_syntax *>(temp);
    } catch (const std::exception &e) {
      std::cerr << e.what() << " number -> primary_expr" << '\n';
    }
  }
}

antlrcpp::Any syntax_tree_builder::visitNumber(C1Parser::NumberContext *ctx) {
  // std::cout<<"enter number"<<std::endl;
  auto result = new literal_syntax;
  auto intConst = ctx->IntConst();
  result->line = intConst->getSymbol()->getLine();
  result->pos = intConst->getSymbol()->getCharPositionInLine();
  auto text = intConst->getSymbol()->getText();
  if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) // Hexadecimal
    result->intConst = std::stoi(text, nullptr, 16);        // std::stoi will eat '0x'
  /* you need to add other situations here */
  else if (text[0] == '0') {
    result->intConst = std::stoi(text, nullptr, 8);
  } else {
    result->intConst = std::stoi(text, nullptr, 10);
  }
  return result;
}

ptr<syntax_tree_node> syntax_tree_builder::operator()(antlr4::tree::ParseTree *ctx) {
  auto result = visit(ctx);
  if (result.is<syntax_tree_node *>())
    return ptr<syntax_tree_node>(result.as<syntax_tree_node *>());
  if (result.is<assembly *>())
    return ptr<syntax_tree_node>(result.as<assembly *>());
  if (result.is<global_def_syntax *>())
    return ptr<syntax_tree_node>(result.as<global_def_syntax *>());
  if (result.is<const_def_stmt_syntax *>())
    return ptr<syntax_tree_node>(result.as<const_def_stmt_syntax *>());
  if (result.is<var_def_stmt_syntax *>())
    return ptr<syntax_tree_node>(result.as<var_def_stmt_syntax *>());
  if (result.is<init_var_syntax *>())
    return ptr<syntax_tree_node>(result.as<init_var_syntax *>());
  if (result.is<init_const_syntax *>())
    return ptr<syntax_tree_node>(result.as<init_const_syntax *>());
  if (result.is<func_def_syntax *>())
    return ptr<syntax_tree_node>(result.as<func_def_syntax *>());
  if (result.is<func_def_param_syntax *>())
    return ptr<syntax_tree_node>(result.as<func_def_param_syntax *>());
  if (result.is<stmt_syntax *>())
    return ptr<syntax_tree_node>(result.as<stmt_syntax *>());
  if (result.is<assign_stmt_syntax *>())
    return ptr<syntax_tree_node>(result.as<assign_stmt_syntax *>());
  if (result.is<expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<expr_syntax *>());
  if (result.is<block_syntax *>())
    return ptr<syntax_tree_node>(result.as<block_syntax *>());
  if (result.is<if_stmt_syntax *>())
    return ptr<syntax_tree_node>(result.as<if_stmt_syntax *>());
  if (result.is<while_stmt_syntax *>())
    return ptr<syntax_tree_node>(result.as<while_stmt_syntax *>());
  if (result.is<const_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<const_expr_syntax *>());

  if (result.is<add_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<add_expr_syntax *>());
  if (result.is<addop_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<addop_expr_syntax *>());
  if (result.is<mul_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<mul_expr_syntax *>());
  if (result.is<mulop_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<mulop_expr_syntax *>());
  if (result.is<unary_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<unary_expr_syntax *>());
  if (result.is<func_call_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<func_call_expr_syntax *>());
  if (result.is<unaryop_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<unaryop_expr_syntax *>());
  if (result.is<primary_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<primary_expr_syntax *>());
  if (result.is<internal_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<internal_expr_syntax *>());

  if (result.is<literal_syntax *>())
    return ptr<syntax_tree_node>(result.as<literal_syntax *>());
  if (result.is<lval_syntax *>())
    return ptr<syntax_tree_node>(result.as<lval_syntax *>());
  if (result.is<cond_syntax *>())
    return ptr<syntax_tree_node>(result.as<cond_syntax *>());
  if (result.is<lor_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<lor_expr_syntax *>());
  if (result.is<lorop_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<lorop_expr_syntax *>());
  if (result.is<land_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<land_expr_syntax *>());
  if (result.is<landop_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<landop_expr_syntax *>());
  if (result.is<eq_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<eq_expr_syntax *>());
  if (result.is<eqop_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<eqop_expr_syntax *>());
  if (result.is<rel_expr_syntax *>())
    return ptr<syntax_tree_node>(result.as<rel_expr_syntax *>());

  return nullptr;
}
