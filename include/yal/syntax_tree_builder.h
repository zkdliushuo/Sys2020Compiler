
#ifndef _C1_SYNTAX_TREE_BUILDER_H_
#define _C1_SYNTAX_TREE_BUILDER_H_

#include "C1ParserBaseVisitor.h"
#include "error_reporter.h"
#include "syntax_tree.h"

namespace c1_recognizer {
namespace syntax_tree {
class syntax_tree_builder : public C1ParserBaseVisitor {
public:
  syntax_tree_builder(error_reporter &_err);

  virtual antlrcpp::Any visitCompilationUnit(C1Parser::CompilationUnitContext *ctx) override;
  virtual antlrcpp::Any visitDecl(C1Parser::DeclContext *ctx) override;
  virtual antlrcpp::Any visitConstdecl(C1Parser::ConstdeclContext *ctx) override;
  virtual antlrcpp::Any visitConstdef(C1Parser::ConstdefContext *ctx) override;
  virtual antlrcpp::Any visitConstinitval(C1Parser::ConstinitvalContext *ctx) override;
  virtual antlrcpp::Any visitConstexp(C1Parser::ConstexpContext *ctx) override;
  virtual antlrcpp::Any visitVardecl(C1Parser::VardeclContext *ctx) override;
  virtual antlrcpp::Any visitVardef(C1Parser::VardefContext *ctx) override;
  virtual antlrcpp::Any visitInitval(C1Parser::InitvalContext *ctx) override;
  virtual antlrcpp::Any visitFuncdef(C1Parser::FuncdefContext *ctx) override;
  // virtual antlrcpp::Any visitFuncfparams(C1Parser::FuncfparamsContext *ctx) override ;
  virtual antlrcpp::Any visitFuncfparam(C1Parser::FuncfparamContext *ctx) override;
  // virtual antlrcpp::Any visitFunctype(C1Parser::FunctypeContext *ctx) override ;
  virtual antlrcpp::Any visitBlock(C1Parser::BlockContext *ctx) override;
  // virtual antlrcpp::Any visitBlockbody(C1Parser::BlockbodyContext *ctx) override ;
  virtual antlrcpp::Any visitStmt(C1Parser::StmtContext *ctx) override;
  virtual antlrcpp::Any visitExp(C1Parser::ExpContext *ctx) override;
  virtual antlrcpp::Any visitCond(C1Parser::CondContext *ctx) override;
  virtual antlrcpp::Any visitLval(C1Parser::LvalContext *ctx) override;
  virtual antlrcpp::Any visitPrimaryexp(C1Parser::PrimaryexpContext *ctx) override;
  virtual antlrcpp::Any visitUnaryexp(C1Parser::UnaryexpContext *ctx) override;
  // virtual antlrcpp::Any visitUnaryop(C1Parser::UnaryopContext *ctx) override ;
  // virtual antlrcpp::Any visitFuncrparams(C1Parser::FuncrparamsContext *ctx) override ;
  virtual antlrcpp::Any visitMulexp(C1Parser::MulexpContext *ctx) override;
  virtual antlrcpp::Any visitAddexp(C1Parser::AddexpContext *ctx) override;
  virtual antlrcpp::Any visitRelexp(C1Parser::RelexpContext *ctx) override;
  virtual antlrcpp::Any visitEqexp(C1Parser::EqexpContext *ctx) override;
  virtual antlrcpp::Any visitLandexp(C1Parser::LandexpContext *ctx) override;
  virtual antlrcpp::Any visitLorexp(C1Parser::LorexpContext *ctx) override;
  virtual antlrcpp::Any visitNumber(C1Parser::NumberContext *ctx) override;
  ptr<syntax_tree_node> operator()(antlr4::tree::ParseTree *ctx);

private:
  error_reporter &err;
};
} // namespace syntax_tree
} // namespace c1_recognizer

#endif
