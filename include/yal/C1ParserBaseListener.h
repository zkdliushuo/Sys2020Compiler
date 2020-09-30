
// Generated from /home/chivier/compiler/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.2

#pragma once

#include <bits/stdc++.h>

#include "C1ParserListener.h"
#include <antlr4-runtime.h>

/**
 * This class provides an empty implementation of C1ParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class C1ParserBaseListener : public C1ParserListener {
public:
  virtual void enterCompilationUnit(C1Parser::CompilationUnitContext * /*ctx*/) override {}
  virtual void exitCompilationUnit(C1Parser::CompilationUnitContext * /*ctx*/) override {}

  virtual void enterStart(C1Parser::StartContext * /*ctx*/) override {}
  virtual void exitStart(C1Parser::StartContext * /*ctx*/) override {}

  virtual void enterDecl(C1Parser::DeclContext * /*ctx*/) override {}
  virtual void exitDecl(C1Parser::DeclContext * /*ctx*/) override {}

  virtual void enterConstdecl(C1Parser::ConstdeclContext * /*ctx*/) override {}
  virtual void exitConstdecl(C1Parser::ConstdeclContext * /*ctx*/) override {}

  virtual void enterConstdef(C1Parser::ConstdefContext * /*ctx*/) override {}
  virtual void exitConstdef(C1Parser::ConstdefContext * /*ctx*/) override {}

  virtual void enterConstinitval(C1Parser::ConstinitvalContext * /*ctx*/) override {}
  virtual void exitConstinitval(C1Parser::ConstinitvalContext * /*ctx*/) override {}

  virtual void enterConstexp(C1Parser::ConstexpContext * /*ctx*/) override {}
  virtual void exitConstexp(C1Parser::ConstexpContext * /*ctx*/) override {}

  virtual void enterVardecl(C1Parser::VardeclContext * /*ctx*/) override {}
  virtual void exitVardecl(C1Parser::VardeclContext * /*ctx*/) override {}

  virtual void enterVardef(C1Parser::VardefContext * /*ctx*/) override {}
  virtual void exitVardef(C1Parser::VardefContext * /*ctx*/) override {}

  virtual void enterInitval(C1Parser::InitvalContext * /*ctx*/) override {}
  virtual void exitInitval(C1Parser::InitvalContext * /*ctx*/) override {}

  virtual void enterFuncdef(C1Parser::FuncdefContext * /*ctx*/) override {}
  virtual void exitFuncdef(C1Parser::FuncdefContext * /*ctx*/) override {}

  virtual void enterFuncfparams(C1Parser::FuncfparamsContext * /*ctx*/) override {}
  virtual void exitFuncfparams(C1Parser::FuncfparamsContext * /*ctx*/) override {}

  virtual void enterFuncfparam(C1Parser::FuncfparamContext * /*ctx*/) override {}
  virtual void exitFuncfparam(C1Parser::FuncfparamContext * /*ctx*/) override {}

  virtual void enterFunctype(C1Parser::FunctypeContext * /*ctx*/) override {}
  virtual void exitFunctype(C1Parser::FunctypeContext * /*ctx*/) override {}

  virtual void enterBlock(C1Parser::BlockContext * /*ctx*/) override {}
  virtual void exitBlock(C1Parser::BlockContext * /*ctx*/) override {}

  virtual void enterBlockbody(C1Parser::BlockbodyContext * /*ctx*/) override {}
  virtual void exitBlockbody(C1Parser::BlockbodyContext * /*ctx*/) override {}

  virtual void enterStmt(C1Parser::StmtContext * /*ctx*/) override {}
  virtual void exitStmt(C1Parser::StmtContext * /*ctx*/) override {}

  virtual void enterExp(C1Parser::ExpContext * /*ctx*/) override {}
  virtual void exitExp(C1Parser::ExpContext * /*ctx*/) override {}

  virtual void enterCond(C1Parser::CondContext * /*ctx*/) override {}
  virtual void exitCond(C1Parser::CondContext * /*ctx*/) override {}

  virtual void enterLval(C1Parser::LvalContext * /*ctx*/) override {}
  virtual void exitLval(C1Parser::LvalContext * /*ctx*/) override {}

  virtual void enterPrimaryexp(C1Parser::PrimaryexpContext * /*ctx*/) override {}
  virtual void exitPrimaryexp(C1Parser::PrimaryexpContext * /*ctx*/) override {}

  virtual void enterUnaryexp(C1Parser::UnaryexpContext * /*ctx*/) override {}
  virtual void exitUnaryexp(C1Parser::UnaryexpContext * /*ctx*/) override {}

  virtual void enterUnaryop(C1Parser::UnaryopContext * /*ctx*/) override {}
  virtual void exitUnaryop(C1Parser::UnaryopContext * /*ctx*/) override {}

  virtual void enterFuncrparams(C1Parser::FuncrparamsContext * /*ctx*/) override {}
  virtual void exitFuncrparams(C1Parser::FuncrparamsContext * /*ctx*/) override {}

  virtual void enterMulexp(C1Parser::MulexpContext * /*ctx*/) override {}
  virtual void exitMulexp(C1Parser::MulexpContext * /*ctx*/) override {}

  virtual void enterAddexp(C1Parser::AddexpContext * /*ctx*/) override {}
  virtual void exitAddexp(C1Parser::AddexpContext * /*ctx*/) override {}

  virtual void enterRelexp(C1Parser::RelexpContext * /*ctx*/) override {}
  virtual void exitRelexp(C1Parser::RelexpContext * /*ctx*/) override {}

  virtual void enterEqexp(C1Parser::EqexpContext * /*ctx*/) override {}
  virtual void exitEqexp(C1Parser::EqexpContext * /*ctx*/) override {}

  virtual void enterLandexp(C1Parser::LandexpContext * /*ctx*/) override {}
  virtual void exitLandexp(C1Parser::LandexpContext * /*ctx*/) override {}

  virtual void enterLorexp(C1Parser::LorexpContext * /*ctx*/) override {}
  virtual void exitLorexp(C1Parser::LorexpContext * /*ctx*/) override {}

  virtual void enterNumber(C1Parser::NumberContext * /*ctx*/) override {}
  virtual void exitNumber(C1Parser::NumberContext * /*ctx*/) override {}

  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {}
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {}
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override {}
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override {}
};
