
// Generated from /home/chivier/compiler/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.2

#pragma once

#include <bits/stdc++.h>

#include "C1ParserVisitor.h"
#include <antlr4-runtime.h>

/**
 * This class provides an empty implementation of C1ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class C1ParserBaseVisitor : public C1ParserVisitor {
public:
  virtual antlrcpp::Any visitCompilationUnit(C1Parser::CompilationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStart(C1Parser::StartContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitDecl(C1Parser::DeclContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitConstdecl(C1Parser::ConstdeclContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitConstdef(C1Parser::ConstdefContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitConstinitval(C1Parser::ConstinitvalContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitConstexp(C1Parser::ConstexpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitVardecl(C1Parser::VardeclContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitVardef(C1Parser::VardefContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitInitval(C1Parser::InitvalContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitFuncdef(C1Parser::FuncdefContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitFuncfparams(C1Parser::FuncfparamsContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitFuncfparam(C1Parser::FuncfparamContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitFunctype(C1Parser::FunctypeContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitBlock(C1Parser::BlockContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitBlockbody(C1Parser::BlockbodyContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitStmt(C1Parser::StmtContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitExp(C1Parser::ExpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitCond(C1Parser::CondContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitLval(C1Parser::LvalContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitPrimaryexp(C1Parser::PrimaryexpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitUnaryexp(C1Parser::UnaryexpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitUnaryop(C1Parser::UnaryopContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitFuncrparams(C1Parser::FuncrparamsContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitMulexp(C1Parser::MulexpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitAddexp(C1Parser::AddexpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitRelexp(C1Parser::RelexpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitEqexp(C1Parser::EqexpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitLandexp(C1Parser::LandexpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitLorexp(C1Parser::LorexpContext *ctx) override { return visitChildren(ctx); }

  virtual antlrcpp::Any visitNumber(C1Parser::NumberContext *ctx) override { return visitChildren(ctx); }
};
