
// Generated from /home/chivier/compiler/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.2

#pragma once

#include <bits/stdc++.h>

#include "C1Parser.h"
#include <antlr4-runtime.h>

/**
 * This class defines an abstract visitor for a parse tree
 * produced by C1Parser.
 */
class C1ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:
  /**
   * Visit parse trees produced by C1Parser.
   */
  virtual antlrcpp::Any visitCompilationUnit(C1Parser::CompilationUnitContext *context) = 0;

  virtual antlrcpp::Any visitStart(C1Parser::StartContext *context) = 0;

  virtual antlrcpp::Any visitDecl(C1Parser::DeclContext *context) = 0;

  virtual antlrcpp::Any visitConstdecl(C1Parser::ConstdeclContext *context) = 0;

  virtual antlrcpp::Any visitConstdef(C1Parser::ConstdefContext *context) = 0;

  virtual antlrcpp::Any visitConstinitval(C1Parser::ConstinitvalContext *context) = 0;

  virtual antlrcpp::Any visitConstexp(C1Parser::ConstexpContext *context) = 0;

  virtual antlrcpp::Any visitVardecl(C1Parser::VardeclContext *context) = 0;

  virtual antlrcpp::Any visitVardef(C1Parser::VardefContext *context) = 0;

  virtual antlrcpp::Any visitInitval(C1Parser::InitvalContext *context) = 0;

  virtual antlrcpp::Any visitFuncdef(C1Parser::FuncdefContext *context) = 0;

  virtual antlrcpp::Any visitFuncfparams(C1Parser::FuncfparamsContext *context) = 0;

  virtual antlrcpp::Any visitFuncfparam(C1Parser::FuncfparamContext *context) = 0;

  virtual antlrcpp::Any visitFunctype(C1Parser::FunctypeContext *context) = 0;

  virtual antlrcpp::Any visitBlock(C1Parser::BlockContext *context) = 0;

  virtual antlrcpp::Any visitBlockbody(C1Parser::BlockbodyContext *context) = 0;

  virtual antlrcpp::Any visitStmt(C1Parser::StmtContext *context) = 0;

  virtual antlrcpp::Any visitExp(C1Parser::ExpContext *context) = 0;

  virtual antlrcpp::Any visitCond(C1Parser::CondContext *context) = 0;

  virtual antlrcpp::Any visitLval(C1Parser::LvalContext *context) = 0;

  virtual antlrcpp::Any visitPrimaryexp(C1Parser::PrimaryexpContext *context) = 0;

  virtual antlrcpp::Any visitUnaryexp(C1Parser::UnaryexpContext *context) = 0;

  virtual antlrcpp::Any visitUnaryop(C1Parser::UnaryopContext *context) = 0;

  virtual antlrcpp::Any visitFuncrparams(C1Parser::FuncrparamsContext *context) = 0;

  virtual antlrcpp::Any visitMulexp(C1Parser::MulexpContext *context) = 0;

  virtual antlrcpp::Any visitAddexp(C1Parser::AddexpContext *context) = 0;

  virtual antlrcpp::Any visitRelexp(C1Parser::RelexpContext *context) = 0;

  virtual antlrcpp::Any visitEqexp(C1Parser::EqexpContext *context) = 0;

  virtual antlrcpp::Any visitLandexp(C1Parser::LandexpContext *context) = 0;

  virtual antlrcpp::Any visitLorexp(C1Parser::LorexpContext *context) = 0;

  virtual antlrcpp::Any visitNumber(C1Parser::NumberContext *context) = 0;
};
