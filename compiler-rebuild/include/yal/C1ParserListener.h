
// Generated from /home/chivier/compiler/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.2

#pragma once

#include <bits/stdc++.h>

#include "C1Parser.h"
#include <antlr4-runtime.h>

/**
 * This interface defines an abstract listener for a parse tree produced by C1Parser.
 */
class C1ParserListener : public antlr4::tree::ParseTreeListener {
public:
  virtual void enterCompilationUnit(C1Parser::CompilationUnitContext *ctx) = 0;
  virtual void exitCompilationUnit(C1Parser::CompilationUnitContext *ctx) = 0;

  virtual void enterStart(C1Parser::StartContext *ctx) = 0;
  virtual void exitStart(C1Parser::StartContext *ctx) = 0;

  virtual void enterDecl(C1Parser::DeclContext *ctx) = 0;
  virtual void exitDecl(C1Parser::DeclContext *ctx) = 0;

  virtual void enterConstdecl(C1Parser::ConstdeclContext *ctx) = 0;
  virtual void exitConstdecl(C1Parser::ConstdeclContext *ctx) = 0;

  virtual void enterConstdef(C1Parser::ConstdefContext *ctx) = 0;
  virtual void exitConstdef(C1Parser::ConstdefContext *ctx) = 0;

  virtual void enterConstinitval(C1Parser::ConstinitvalContext *ctx) = 0;
  virtual void exitConstinitval(C1Parser::ConstinitvalContext *ctx) = 0;

  virtual void enterConstexp(C1Parser::ConstexpContext *ctx) = 0;
  virtual void exitConstexp(C1Parser::ConstexpContext *ctx) = 0;

  virtual void enterVardecl(C1Parser::VardeclContext *ctx) = 0;
  virtual void exitVardecl(C1Parser::VardeclContext *ctx) = 0;

  virtual void enterVardef(C1Parser::VardefContext *ctx) = 0;
  virtual void exitVardef(C1Parser::VardefContext *ctx) = 0;

  virtual void enterInitval(C1Parser::InitvalContext *ctx) = 0;
  virtual void exitInitval(C1Parser::InitvalContext *ctx) = 0;

  virtual void enterFuncdef(C1Parser::FuncdefContext *ctx) = 0;
  virtual void exitFuncdef(C1Parser::FuncdefContext *ctx) = 0;

  virtual void enterFuncfparams(C1Parser::FuncfparamsContext *ctx) = 0;
  virtual void exitFuncfparams(C1Parser::FuncfparamsContext *ctx) = 0;

  virtual void enterFuncfparam(C1Parser::FuncfparamContext *ctx) = 0;
  virtual void exitFuncfparam(C1Parser::FuncfparamContext *ctx) = 0;

  virtual void enterFunctype(C1Parser::FunctypeContext *ctx) = 0;
  virtual void exitFunctype(C1Parser::FunctypeContext *ctx) = 0;

  virtual void enterBlock(C1Parser::BlockContext *ctx) = 0;
  virtual void exitBlock(C1Parser::BlockContext *ctx) = 0;

  virtual void enterBlockbody(C1Parser::BlockbodyContext *ctx) = 0;
  virtual void exitBlockbody(C1Parser::BlockbodyContext *ctx) = 0;

  virtual void enterStmt(C1Parser::StmtContext *ctx) = 0;
  virtual void exitStmt(C1Parser::StmtContext *ctx) = 0;

  virtual void enterExp(C1Parser::ExpContext *ctx) = 0;
  virtual void exitExp(C1Parser::ExpContext *ctx) = 0;

  virtual void enterCond(C1Parser::CondContext *ctx) = 0;
  virtual void exitCond(C1Parser::CondContext *ctx) = 0;

  virtual void enterLval(C1Parser::LvalContext *ctx) = 0;
  virtual void exitLval(C1Parser::LvalContext *ctx) = 0;

  virtual void enterPrimaryexp(C1Parser::PrimaryexpContext *ctx) = 0;
  virtual void exitPrimaryexp(C1Parser::PrimaryexpContext *ctx) = 0;

  virtual void enterUnaryexp(C1Parser::UnaryexpContext *ctx) = 0;
  virtual void exitUnaryexp(C1Parser::UnaryexpContext *ctx) = 0;

  virtual void enterUnaryop(C1Parser::UnaryopContext *ctx) = 0;
  virtual void exitUnaryop(C1Parser::UnaryopContext *ctx) = 0;

  virtual void enterFuncrparams(C1Parser::FuncrparamsContext *ctx) = 0;
  virtual void exitFuncrparams(C1Parser::FuncrparamsContext *ctx) = 0;

  virtual void enterMulexp(C1Parser::MulexpContext *ctx) = 0;
  virtual void exitMulexp(C1Parser::MulexpContext *ctx) = 0;

  virtual void enterAddexp(C1Parser::AddexpContext *ctx) = 0;
  virtual void exitAddexp(C1Parser::AddexpContext *ctx) = 0;

  virtual void enterRelexp(C1Parser::RelexpContext *ctx) = 0;
  virtual void exitRelexp(C1Parser::RelexpContext *ctx) = 0;

  virtual void enterEqexp(C1Parser::EqexpContext *ctx) = 0;
  virtual void exitEqexp(C1Parser::EqexpContext *ctx) = 0;

  virtual void enterLandexp(C1Parser::LandexpContext *ctx) = 0;
  virtual void exitLandexp(C1Parser::LandexpContext *ctx) = 0;

  virtual void enterLorexp(C1Parser::LorexpContext *ctx) = 0;
  virtual void exitLorexp(C1Parser::LorexpContext *ctx) = 0;

  virtual void enterNumber(C1Parser::NumberContext *ctx) = 0;
  virtual void exitNumber(C1Parser::NumberContext *ctx) = 0;
};
