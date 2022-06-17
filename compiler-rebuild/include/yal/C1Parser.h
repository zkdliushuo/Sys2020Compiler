
// Generated from /home/chivier/compiler/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.2

#pragma once

#include <bits/stdc++.h>

#include <antlr4-runtime.h>

class C1Parser : public antlr4::Parser {
public:
  enum {
    Comma = 1,
    SemiColon = 2,
    Assign = 3,
    LeftBracket = 4,
    RightBracket = 5,
    LeftBrace = 6,
    RightBrace = 7,
    LeftParen = 8,
    RightParen = 9,
    If = 10,
    Else = 11,
    While = 12,
    Break = 13,
    Continue = 14,
    Return = 15,
    Const = 16,
    Equal = 17,
    NonEqual = 18,
    Negative = 19,
    LogicalAnd = 20,
    LogicalOr = 21,
    Less = 22,
    Greater = 23,
    LessEqual = 24,
    GreaterEqual = 25,
    Plus = 26,
    Minus = 27,
    Multiply = 28,
    Divide = 29,
    Modulo = 30,
    Int = 31,
    Void = 32,
    Identifier = 33,
    IntConst = 34,
    LineComment = 35,
    BlockComment = 36,
    WhiteSpace = 37
  };

  enum {
    RuleCompilationUnit = 0,
    RuleStart = 1,
    RuleDecl = 2,
    RuleConstdecl = 3,
    RuleConstdef = 4,
    RuleConstinitval = 5,
    RuleConstexp = 6,
    RuleVardecl = 7,
    RuleVardef = 8,
    RuleInitval = 9,
    RuleFuncdef = 10,
    RuleFuncfparams = 11,
    RuleFuncfparam = 12,
    RuleFunctype = 13,
    RuleBlock = 14,
    RuleBlockbody = 15,
    RuleStmt = 16,
    RuleExp = 17,
    RuleCond = 18,
    RuleLval = 19,
    RulePrimaryexp = 20,
    RuleUnaryexp = 21,
    RuleUnaryop = 22,
    RuleFuncrparams = 23,
    RuleMulexp = 24,
    RuleAddexp = 25,
    RuleRelexp = 26,
    RuleEqexp = 27,
    RuleLandexp = 28,
    RuleLorexp = 29,
    RuleNumber = 30
  };

  C1Parser(antlr4::TokenStream *input);
  ~C1Parser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN &getATN() const override { return _atn; };
  virtual const std::vector<std::string> &getTokenNames() const override {
    return _tokenNames;
  }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string> &getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary &getVocabulary() const override;

  class CompilationUnitContext;
  class StartContext;
  class DeclContext;
  class ConstdeclContext;
  class ConstdefContext;
  class ConstinitvalContext;
  class ConstexpContext;
  class VardeclContext;
  class VardefContext;
  class InitvalContext;
  class FuncdefContext;
  class FuncfparamsContext;
  class FuncfparamContext;
  class FunctypeContext;
  class BlockContext;
  class BlockbodyContext;
  class StmtContext;
  class ExpContext;
  class CondContext;
  class LvalContext;
  class PrimaryexpContext;
  class UnaryexpContext;
  class UnaryopContext;
  class FuncrparamsContext;
  class MulexpContext;
  class AddexpContext;
  class RelexpContext;
  class EqexpContext;
  class LandexpContext;
  class LorexpContext;
  class NumberContext;

  class CompilationUnitContext : public antlr4::ParserRuleContext {
  public:
    CompilationUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StartContext *> start();
    StartContext *start(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  CompilationUnitContext *compilationUnit();

  class StartContext : public antlr4::ParserRuleContext {
  public:
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclContext *decl();
    FuncdefContext *funcdef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StartContext *start();

  class DeclContext : public antlr4::ParserRuleContext {
  public:
    DeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstdeclContext *constdecl();
    VardeclContext *vardecl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  DeclContext *decl();

  class ConstdeclContext : public antlr4::ParserRuleContext {
  public:
    ConstdeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    antlr4::tree::TerminalNode *Int();
    std::vector<ConstdefContext *> constdef();
    ConstdefContext *constdef(size_t i);
    antlr4::tree::TerminalNode *SemiColon();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode *Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConstdeclContext *constdecl();

  class ConstdefContext : public antlr4::ParserRuleContext {
  public:
    ConstdefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Assign();
    ConstinitvalContext *constinitval();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode *LeftBracket(size_t i);
    std::vector<ConstexpContext *> constexp();
    ConstexpContext *constexp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode *RightBracket(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConstdefContext *constdef();

  class ConstinitvalContext : public antlr4::ParserRuleContext {
  public:
    ConstinitvalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstexpContext *constexp();
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    std::vector<ConstinitvalContext *> constinitval();
    ConstinitvalContext *constinitval(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode *Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConstinitvalContext *constinitval();

  class ConstexpContext : public antlr4::ParserRuleContext {
  public:
    ConstexpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddexpContext *addexp();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConstexpContext *constexp();

  class VardeclContext : public antlr4::ParserRuleContext {
  public:
    VardeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Int();
    std::vector<VardefContext *> vardef();
    VardefContext *vardef(size_t i);
    antlr4::tree::TerminalNode *SemiColon();
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode *Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  VardeclContext *vardecl();

  class VardefContext : public antlr4::ParserRuleContext {
  public:
    VardefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode *LeftBracket(size_t i);
    std::vector<ConstexpContext *> constexp();
    ConstexpContext *constexp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode *RightBracket(size_t i);
    antlr4::tree::TerminalNode *Assign();
    InitvalContext *initval();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  VardefContext *vardef();

  class InitvalContext : public antlr4::ParserRuleContext {
  public:
    InitvalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpContext *exp();
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    std::vector<InitvalContext *> initval();
    InitvalContext *initval(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode *Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  InitvalContext *initval();

  class FuncdefContext : public antlr4::ParserRuleContext {
  public:
    FuncdefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctypeContext *functype();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    BlockContext *block();
    FuncfparamsContext *funcfparams();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FuncdefContext *funcdef();

  class FuncfparamsContext : public antlr4::ParserRuleContext {
  public:
    FuncfparamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FuncfparamContext *> funcfparam();
    FuncfparamContext *funcfparam(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode *Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FuncfparamsContext *funcfparams();

  class FuncfparamContext : public antlr4::ParserRuleContext {
  public:
    FuncfparamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Int();
    antlr4::tree::TerminalNode *Identifier();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode *LeftBracket(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode *RightBracket(size_t i);
    std::vector<ExpContext *> exp();
    ExpContext *exp(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FuncfparamContext *funcfparam();

  class FunctypeContext : public antlr4::ParserRuleContext {
  public:
    FunctypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Void();
    antlr4::tree::TerminalNode *Int();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FunctypeContext *functype();

  class BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBrace();
    antlr4::tree::TerminalNode *RightBrace();
    std::vector<BlockbodyContext *> blockbody();
    BlockbodyContext *blockbody(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BlockContext *block();

  class BlockbodyContext : public antlr4::ParserRuleContext {
  public:
    BlockbodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclContext *decl();
    StmtContext *stmt();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BlockbodyContext *blockbody();

  class StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LvalContext *lval();
    antlr4::tree::TerminalNode *Assign();
    ExpContext *exp();
    antlr4::tree::TerminalNode *SemiColon();
    BlockContext *block();
    antlr4::tree::TerminalNode *If();
    antlr4::tree::TerminalNode *LeftParen();
    CondContext *cond();
    antlr4::tree::TerminalNode *RightParen();
    std::vector<StmtContext *> stmt();
    StmtContext *stmt(size_t i);
    antlr4::tree::TerminalNode *Else();
    antlr4::tree::TerminalNode *While();
    antlr4::tree::TerminalNode *Break();
    antlr4::tree::TerminalNode *Continue();
    antlr4::tree::TerminalNode *Return();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StmtContext *stmt();

  class ExpContext : public antlr4::ParserRuleContext {
  public:
    ExpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddexpContext *addexp();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpContext *exp();

  class CondContext : public antlr4::ParserRuleContext {
  public:
    CondContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LorexpContext *lorexp();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  CondContext *cond();

  class LvalContext : public antlr4::ParserRuleContext {
  public:
    LvalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    std::vector<antlr4::tree::TerminalNode *> LeftBracket();
    antlr4::tree::TerminalNode *LeftBracket(size_t i);
    std::vector<ExpContext *> exp();
    ExpContext *exp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RightBracket();
    antlr4::tree::TerminalNode *RightBracket(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LvalContext *lval();

  class PrimaryexpContext : public antlr4::ParserRuleContext {
  public:
    PrimaryexpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftParen();
    ExpContext *exp();
    antlr4::tree::TerminalNode *RightParen();
    LvalContext *lval();
    NumberContext *number();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PrimaryexpContext *primaryexp();

  class UnaryexpContext : public antlr4::ParserRuleContext {
  public:
    UnaryexpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryexpContext *primaryexp();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *LeftParen();
    antlr4::tree::TerminalNode *RightParen();
    FuncrparamsContext *funcrparams();
    UnaryopContext *unaryop();
    UnaryexpContext *unaryexp();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryexpContext *unaryexp();

  class UnaryopContext : public antlr4::ParserRuleContext {
  public:
    UnaryopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();
    antlr4::tree::TerminalNode *Negative();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryopContext *unaryop();

  class FuncrparamsContext : public antlr4::ParserRuleContext {
  public:
    FuncrparamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpContext *> exp();
    ExpContext *exp(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode *Comma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FuncrparamsContext *funcrparams();

  class MulexpContext : public antlr4::ParserRuleContext {
  public:
    MulexpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryexpContext *unaryexp();
    MulexpContext *mulexp();
    antlr4::tree::TerminalNode *Multiply();
    antlr4::tree::TerminalNode *Divide();
    antlr4::tree::TerminalNode *Modulo();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MulexpContext *mulexp();
  MulexpContext *mulexp(int precedence);
  class AddexpContext : public antlr4::ParserRuleContext {
  public:
    AddexpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MulexpContext *mulexp();
    AddexpContext *addexp();
    antlr4::tree::TerminalNode *Plus();
    antlr4::tree::TerminalNode *Minus();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AddexpContext *addexp();
  AddexpContext *addexp(int precedence);
  class RelexpContext : public antlr4::ParserRuleContext {
  public:
    RelexpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddexpContext *addexp();
    RelexpContext *relexp();
    antlr4::tree::TerminalNode *Less();
    antlr4::tree::TerminalNode *Greater();
    antlr4::tree::TerminalNode *LessEqual();
    antlr4::tree::TerminalNode *GreaterEqual();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  RelexpContext *relexp();
  RelexpContext *relexp(int precedence);
  class EqexpContext : public antlr4::ParserRuleContext {
  public:
    EqexpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RelexpContext *relexp();
    EqexpContext *eqexp();
    antlr4::tree::TerminalNode *Equal();
    antlr4::tree::TerminalNode *NonEqual();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  EqexpContext *eqexp();
  EqexpContext *eqexp(int precedence);
  class LandexpContext : public antlr4::ParserRuleContext {
  public:
    LandexpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EqexpContext *eqexp();
    LandexpContext *landexp();
    antlr4::tree::TerminalNode *LogicalAnd();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LandexpContext *landexp();
  LandexpContext *landexp(int precedence);
  class LorexpContext : public antlr4::ParserRuleContext {
  public:
    LorexpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LandexpContext *landexp();
    LorexpContext *lorexp();
    antlr4::tree::TerminalNode *LogicalOr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LorexpContext *lorexp();
  LorexpContext *lorexp(int precedence);
  class NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntConst();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  NumberContext *number();

  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool mulexpSempred(MulexpContext *_localctx, size_t predicateIndex);
  bool addexpSempred(AddexpContext *_localctx, size_t predicateIndex);
  bool relexpSempred(RelexpContext *_localctx, size_t predicateIndex);
  bool eqexpSempred(EqexpContext *_localctx, size_t predicateIndex);
  bool landexpSempred(LandexpContext *_localctx, size_t predicateIndex);
  bool lorexpSempred(LorexpContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};
