
// Generated from /home/chivier/compiler/c1recognizer/grammar/C1Parser.g4 by ANTLR 4.7.2

#include "C1ParserListener.h"
#include "C1ParserVisitor.h"

#include "C1Parser.h"

using namespace antlrcpp;
using namespace antlr4;

C1Parser::C1Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

C1Parser::~C1Parser() { delete _interpreter; }

std::string C1Parser::getGrammarFileName() const { return "C1Parser.g4"; }

const std::vector<std::string> &C1Parser::getRuleNames() const { return _ruleNames; }

dfa::Vocabulary &C1Parser::getVocabulary() const { return _vocabulary; }

//----------------- CompilationUnitContext ------------------------------------------------------------------

C1Parser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<C1Parser::StartContext *> C1Parser::CompilationUnitContext::start() {
  return getRuleContexts<C1Parser::StartContext>();
}

C1Parser::StartContext *C1Parser::CompilationUnitContext::start(size_t i) {
  return getRuleContext<C1Parser::StartContext>(i);
}

size_t C1Parser::CompilationUnitContext::getRuleIndex() const { return C1Parser::RuleCompilationUnit; }

void C1Parser::CompilationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompilationUnit(this);
}

void C1Parser::CompilationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompilationUnit(this);
}

antlrcpp::Any C1Parser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::CompilationUnitContext *C1Parser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, C1Parser::RuleCompilationUnit);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(62);
      start();
      setState(65);
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~0x3fULL) == 0) &&
              ((1ULL << _la) & ((1ULL << C1Parser::Const) | (1ULL << C1Parser::Int) | (1ULL << C1Parser::Void))) != 0));

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartContext ------------------------------------------------------------------

C1Parser::StartContext::StartContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::DeclContext *C1Parser::StartContext::decl() { return getRuleContext<C1Parser::DeclContext>(0); }

C1Parser::FuncdefContext *C1Parser::StartContext::funcdef() { return getRuleContext<C1Parser::FuncdefContext>(0); }

size_t C1Parser::StartContext::getRuleIndex() const { return C1Parser::RuleStart; }

void C1Parser::StartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStart(this);
}

void C1Parser::StartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStart(this);
}

antlrcpp::Any C1Parser::StartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitStart(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::StartContext *C1Parser::start() {
  StartContext *_localctx = _tracker.createInstance<StartContext>(_ctx, getState());
  enterRule(_localctx, 2, C1Parser::RuleStart);

  auto onExit = finally([=] { exitRule(); });
  try {
    setState(69);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(67);
      decl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(68);
      funcdef();
      break;
    }
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

C1Parser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::ConstdeclContext *C1Parser::DeclContext::constdecl() { return getRuleContext<C1Parser::ConstdeclContext>(0); }

C1Parser::VardeclContext *C1Parser::DeclContext::vardecl() { return getRuleContext<C1Parser::VardeclContext>(0); }

size_t C1Parser::DeclContext::getRuleIndex() const { return C1Parser::RuleDecl; }

void C1Parser::DeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecl(this);
}

void C1Parser::DeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecl(this);
}

antlrcpp::Any C1Parser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::DeclContext *C1Parser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 4, C1Parser::RuleDecl);

  auto onExit = finally([=] { exitRule(); });
  try {
    setState(73);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case C1Parser::Const: {
      enterOuterAlt(_localctx, 1);
      setState(71);
      constdecl();
      break;
    }

    case C1Parser::Int: {
      enterOuterAlt(_localctx, 2);
      setState(72);
      vardecl();
      break;
    }

    default:
      throw NoViableAltException(this);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstdeclContext ------------------------------------------------------------------

C1Parser::ConstdeclContext::ConstdeclContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::ConstdeclContext::Const() { return getToken(C1Parser::Const, 0); }

tree::TerminalNode *C1Parser::ConstdeclContext::Int() { return getToken(C1Parser::Int, 0); }

std::vector<C1Parser::ConstdefContext *> C1Parser::ConstdeclContext::constdef() {
  return getRuleContexts<C1Parser::ConstdefContext>();
}

C1Parser::ConstdefContext *C1Parser::ConstdeclContext::constdef(size_t i) {
  return getRuleContext<C1Parser::ConstdefContext>(i);
}

tree::TerminalNode *C1Parser::ConstdeclContext::SemiColon() { return getToken(C1Parser::SemiColon, 0); }

std::vector<tree::TerminalNode *> C1Parser::ConstdeclContext::Comma() { return getTokens(C1Parser::Comma); }

tree::TerminalNode *C1Parser::ConstdeclContext::Comma(size_t i) { return getToken(C1Parser::Comma, i); }

size_t C1Parser::ConstdeclContext::getRuleIndex() const { return C1Parser::RuleConstdecl; }

void C1Parser::ConstdeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstdecl(this);
}

void C1Parser::ConstdeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstdecl(this);
}

antlrcpp::Any C1Parser::ConstdeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitConstdecl(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::ConstdeclContext *C1Parser::constdecl() {
  ConstdeclContext *_localctx = _tracker.createInstance<ConstdeclContext>(_ctx, getState());
  enterRule(_localctx, 6, C1Parser::RuleConstdecl);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    match(C1Parser::Const);
    setState(76);
    match(C1Parser::Int);
    setState(77);
    constdef();
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C1Parser::Comma) {
      setState(78);
      match(C1Parser::Comma);
      setState(79);
      constdef();
      setState(84);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(85);
    match(C1Parser::SemiColon);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstdefContext ------------------------------------------------------------------

C1Parser::ConstdefContext::ConstdefContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::ConstdefContext::Identifier() { return getToken(C1Parser::Identifier, 0); }

tree::TerminalNode *C1Parser::ConstdefContext::Assign() { return getToken(C1Parser::Assign, 0); }

C1Parser::ConstinitvalContext *C1Parser::ConstdefContext::constinitval() {
  return getRuleContext<C1Parser::ConstinitvalContext>(0);
}

std::vector<tree::TerminalNode *> C1Parser::ConstdefContext::LeftBracket() { return getTokens(C1Parser::LeftBracket); }

tree::TerminalNode *C1Parser::ConstdefContext::LeftBracket(size_t i) { return getToken(C1Parser::LeftBracket, i); }

std::vector<C1Parser::ConstexpContext *> C1Parser::ConstdefContext::constexp() {
  return getRuleContexts<C1Parser::ConstexpContext>();
}

C1Parser::ConstexpContext *C1Parser::ConstdefContext::constexp(size_t i) {
  return getRuleContext<C1Parser::ConstexpContext>(i);
}

std::vector<tree::TerminalNode *> C1Parser::ConstdefContext::RightBracket() {
  return getTokens(C1Parser::RightBracket);
}

tree::TerminalNode *C1Parser::ConstdefContext::RightBracket(size_t i) { return getToken(C1Parser::RightBracket, i); }

size_t C1Parser::ConstdefContext::getRuleIndex() const { return C1Parser::RuleConstdef; }

void C1Parser::ConstdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstdef(this);
}

void C1Parser::ConstdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstdef(this);
}

antlrcpp::Any C1Parser::ConstdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitConstdef(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::ConstdefContext *C1Parser::constdef() {
  ConstdefContext *_localctx = _tracker.createInstance<ConstdefContext>(_ctx, getState());
  enterRule(_localctx, 8, C1Parser::RuleConstdef);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    match(C1Parser::Identifier);
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C1Parser::LeftBracket) {
      setState(88);
      match(C1Parser::LeftBracket);
      setState(89);
      constexp();
      setState(90);
      match(C1Parser::RightBracket);
      setState(96);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(97);
    match(C1Parser::Assign);
    setState(98);
    constinitval();

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstinitvalContext ------------------------------------------------------------------

C1Parser::ConstinitvalContext::ConstinitvalContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::ConstexpContext *C1Parser::ConstinitvalContext::constexp() {
  return getRuleContext<C1Parser::ConstexpContext>(0);
}

tree::TerminalNode *C1Parser::ConstinitvalContext::LeftBrace() { return getToken(C1Parser::LeftBrace, 0); }

tree::TerminalNode *C1Parser::ConstinitvalContext::RightBrace() { return getToken(C1Parser::RightBrace, 0); }

std::vector<C1Parser::ConstinitvalContext *> C1Parser::ConstinitvalContext::constinitval() {
  return getRuleContexts<C1Parser::ConstinitvalContext>();
}

C1Parser::ConstinitvalContext *C1Parser::ConstinitvalContext::constinitval(size_t i) {
  return getRuleContext<C1Parser::ConstinitvalContext>(i);
}

std::vector<tree::TerminalNode *> C1Parser::ConstinitvalContext::Comma() { return getTokens(C1Parser::Comma); }

tree::TerminalNode *C1Parser::ConstinitvalContext::Comma(size_t i) { return getToken(C1Parser::Comma, i); }

size_t C1Parser::ConstinitvalContext::getRuleIndex() const { return C1Parser::RuleConstinitval; }

void C1Parser::ConstinitvalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstinitval(this);
}

void C1Parser::ConstinitvalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstinitval(this);
}

antlrcpp::Any C1Parser::ConstinitvalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitConstinitval(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::ConstinitvalContext *C1Parser::constinitval() {
  ConstinitvalContext *_localctx = _tracker.createInstance<ConstinitvalContext>(_ctx, getState());
  enterRule(_localctx, 10, C1Parser::RuleConstinitval);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    setState(113);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case C1Parser::LeftParen:
    case C1Parser::Negative:
    case C1Parser::Plus:
    case C1Parser::Minus:
    case C1Parser::Identifier:
    case C1Parser::IntConst: {
      enterOuterAlt(_localctx, 1);
      setState(100);
      constexp();
      break;
    }

    case C1Parser::LeftBrace: {
      enterOuterAlt(_localctx, 2);
      setState(101);
      match(C1Parser::LeftBrace);
      setState(110);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) & ((1ULL << C1Parser::LeftBrace) | (1ULL << C1Parser::LeftParen) |
                             (1ULL << C1Parser::Negative) | (1ULL << C1Parser::Plus) | (1ULL << C1Parser::Minus) |
                             (1ULL << C1Parser::Identifier) | (1ULL << C1Parser::IntConst))) != 0)) {
        setState(102);
        constinitval();
        setState(107);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == C1Parser::Comma) {
          setState(103);
          match(C1Parser::Comma);
          setState(104);
          constinitval();
          setState(109);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(112);
      match(C1Parser::RightBrace);
      break;
    }

    default:
      throw NoViableAltException(this);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstexpContext ------------------------------------------------------------------

C1Parser::ConstexpContext::ConstexpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::AddexpContext *C1Parser::ConstexpContext::addexp() { return getRuleContext<C1Parser::AddexpContext>(0); }

size_t C1Parser::ConstexpContext::getRuleIndex() const { return C1Parser::RuleConstexp; }

void C1Parser::ConstexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstexp(this);
}

void C1Parser::ConstexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstexp(this);
}

antlrcpp::Any C1Parser::ConstexpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitConstexp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::ConstexpContext *C1Parser::constexp() {
  ConstexpContext *_localctx = _tracker.createInstance<ConstexpContext>(_ctx, getState());
  enterRule(_localctx, 12, C1Parser::RuleConstexp);

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    addexp(0);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardeclContext ------------------------------------------------------------------

C1Parser::VardeclContext::VardeclContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::VardeclContext::Int() { return getToken(C1Parser::Int, 0); }

std::vector<C1Parser::VardefContext *> C1Parser::VardeclContext::vardef() {
  return getRuleContexts<C1Parser::VardefContext>();
}

C1Parser::VardefContext *C1Parser::VardeclContext::vardef(size_t i) {
  return getRuleContext<C1Parser::VardefContext>(i);
}

tree::TerminalNode *C1Parser::VardeclContext::SemiColon() { return getToken(C1Parser::SemiColon, 0); }

std::vector<tree::TerminalNode *> C1Parser::VardeclContext::Comma() { return getTokens(C1Parser::Comma); }

tree::TerminalNode *C1Parser::VardeclContext::Comma(size_t i) { return getToken(C1Parser::Comma, i); }

size_t C1Parser::VardeclContext::getRuleIndex() const { return C1Parser::RuleVardecl; }

void C1Parser::VardeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVardecl(this);
}

void C1Parser::VardeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVardecl(this);
}

antlrcpp::Any C1Parser::VardeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitVardecl(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::VardeclContext *C1Parser::vardecl() {
  VardeclContext *_localctx = _tracker.createInstance<VardeclContext>(_ctx, getState());
  enterRule(_localctx, 14, C1Parser::RuleVardecl);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    match(C1Parser::Int);
    setState(118);
    vardef();
    setState(123);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C1Parser::Comma) {
      setState(119);
      match(C1Parser::Comma);
      setState(120);
      vardef();
      setState(125);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(126);
    match(C1Parser::SemiColon);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardefContext ------------------------------------------------------------------

C1Parser::VardefContext::VardefContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::VardefContext::Identifier() { return getToken(C1Parser::Identifier, 0); }

std::vector<tree::TerminalNode *> C1Parser::VardefContext::LeftBracket() { return getTokens(C1Parser::LeftBracket); }

tree::TerminalNode *C1Parser::VardefContext::LeftBracket(size_t i) { return getToken(C1Parser::LeftBracket, i); }

std::vector<C1Parser::ConstexpContext *> C1Parser::VardefContext::constexp() {
  return getRuleContexts<C1Parser::ConstexpContext>();
}

C1Parser::ConstexpContext *C1Parser::VardefContext::constexp(size_t i) {
  return getRuleContext<C1Parser::ConstexpContext>(i);
}

std::vector<tree::TerminalNode *> C1Parser::VardefContext::RightBracket() { return getTokens(C1Parser::RightBracket); }

tree::TerminalNode *C1Parser::VardefContext::RightBracket(size_t i) { return getToken(C1Parser::RightBracket, i); }

tree::TerminalNode *C1Parser::VardefContext::Assign() { return getToken(C1Parser::Assign, 0); }

C1Parser::InitvalContext *C1Parser::VardefContext::initval() { return getRuleContext<C1Parser::InitvalContext>(0); }

size_t C1Parser::VardefContext::getRuleIndex() const { return C1Parser::RuleVardef; }

void C1Parser::VardefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVardef(this);
}

void C1Parser::VardefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVardef(this);
}

antlrcpp::Any C1Parser::VardefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitVardef(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::VardefContext *C1Parser::vardef() {
  VardefContext *_localctx = _tracker.createInstance<VardefContext>(_ctx, getState());
  enterRule(_localctx, 16, C1Parser::RuleVardef);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    setState(150);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(128);
      match(C1Parser::Identifier);
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C1Parser::LeftBracket) {
        setState(129);
        match(C1Parser::LeftBracket);
        setState(130);
        constexp();
        setState(131);
        match(C1Parser::RightBracket);
        setState(137);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(138);
      match(C1Parser::Identifier);
      setState(145);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C1Parser::LeftBracket) {
        setState(139);
        match(C1Parser::LeftBracket);
        setState(140);
        constexp();
        setState(141);
        match(C1Parser::RightBracket);
        setState(147);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(148);
      match(C1Parser::Assign);
      setState(149);
      initval();
      break;
    }
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitvalContext ------------------------------------------------------------------

C1Parser::InitvalContext::InitvalContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::ExpContext *C1Parser::InitvalContext::exp() { return getRuleContext<C1Parser::ExpContext>(0); }

tree::TerminalNode *C1Parser::InitvalContext::LeftBrace() { return getToken(C1Parser::LeftBrace, 0); }

tree::TerminalNode *C1Parser::InitvalContext::RightBrace() { return getToken(C1Parser::RightBrace, 0); }

std::vector<C1Parser::InitvalContext *> C1Parser::InitvalContext::initval() {
  return getRuleContexts<C1Parser::InitvalContext>();
}

C1Parser::InitvalContext *C1Parser::InitvalContext::initval(size_t i) {
  return getRuleContext<C1Parser::InitvalContext>(i);
}

std::vector<tree::TerminalNode *> C1Parser::InitvalContext::Comma() { return getTokens(C1Parser::Comma); }

tree::TerminalNode *C1Parser::InitvalContext::Comma(size_t i) { return getToken(C1Parser::Comma, i); }

size_t C1Parser::InitvalContext::getRuleIndex() const { return C1Parser::RuleInitval; }

void C1Parser::InitvalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitval(this);
}

void C1Parser::InitvalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitval(this);
}

antlrcpp::Any C1Parser::InitvalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitInitval(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::InitvalContext *C1Parser::initval() {
  InitvalContext *_localctx = _tracker.createInstance<InitvalContext>(_ctx, getState());
  enterRule(_localctx, 18, C1Parser::RuleInitval);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    setState(165);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case C1Parser::LeftParen:
    case C1Parser::Negative:
    case C1Parser::Plus:
    case C1Parser::Minus:
    case C1Parser::Identifier:
    case C1Parser::IntConst: {
      enterOuterAlt(_localctx, 1);
      setState(152);
      exp();
      break;
    }

    case C1Parser::LeftBrace: {
      enterOuterAlt(_localctx, 2);
      setState(153);
      match(C1Parser::LeftBrace);
      setState(162);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) & ((1ULL << C1Parser::LeftBrace) | (1ULL << C1Parser::LeftParen) |
                             (1ULL << C1Parser::Negative) | (1ULL << C1Parser::Plus) | (1ULL << C1Parser::Minus) |
                             (1ULL << C1Parser::Identifier) | (1ULL << C1Parser::IntConst))) != 0)) {
        setState(154);
        initval();
        setState(159);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == C1Parser::Comma) {
          setState(155);
          match(C1Parser::Comma);
          setState(156);
          initval();
          setState(161);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(164);
      match(C1Parser::RightBrace);
      break;
    }

    default:
      throw NoViableAltException(this);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncdefContext ------------------------------------------------------------------

C1Parser::FuncdefContext::FuncdefContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::FunctypeContext *C1Parser::FuncdefContext::functype() { return getRuleContext<C1Parser::FunctypeContext>(0); }

tree::TerminalNode *C1Parser::FuncdefContext::Identifier() { return getToken(C1Parser::Identifier, 0); }

tree::TerminalNode *C1Parser::FuncdefContext::LeftParen() { return getToken(C1Parser::LeftParen, 0); }

tree::TerminalNode *C1Parser::FuncdefContext::RightParen() { return getToken(C1Parser::RightParen, 0); }

C1Parser::BlockContext *C1Parser::FuncdefContext::block() { return getRuleContext<C1Parser::BlockContext>(0); }

C1Parser::FuncfparamsContext *C1Parser::FuncdefContext::funcfparams() {
  return getRuleContext<C1Parser::FuncfparamsContext>(0);
}

size_t C1Parser::FuncdefContext::getRuleIndex() const { return C1Parser::RuleFuncdef; }

void C1Parser::FuncdefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncdef(this);
}

void C1Parser::FuncdefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncdef(this);
}

antlrcpp::Any C1Parser::FuncdefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitFuncdef(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::FuncdefContext *C1Parser::funcdef() {
  FuncdefContext *_localctx = _tracker.createInstance<FuncdefContext>(_ctx, getState());
  enterRule(_localctx, 20, C1Parser::RuleFuncdef);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(167);
    functype();
    setState(168);
    match(C1Parser::Identifier);
    setState(169);
    match(C1Parser::LeftParen);
    setState(171);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C1Parser::Int) {
      setState(170);
      funcfparams();
    }
    setState(173);
    match(C1Parser::RightParen);
    setState(174);
    block();

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncfparamsContext ------------------------------------------------------------------

C1Parser::FuncfparamsContext::FuncfparamsContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<C1Parser::FuncfparamContext *> C1Parser::FuncfparamsContext::funcfparam() {
  return getRuleContexts<C1Parser::FuncfparamContext>();
}

C1Parser::FuncfparamContext *C1Parser::FuncfparamsContext::funcfparam(size_t i) {
  return getRuleContext<C1Parser::FuncfparamContext>(i);
}

std::vector<tree::TerminalNode *> C1Parser::FuncfparamsContext::Comma() { return getTokens(C1Parser::Comma); }

tree::TerminalNode *C1Parser::FuncfparamsContext::Comma(size_t i) { return getToken(C1Parser::Comma, i); }

size_t C1Parser::FuncfparamsContext::getRuleIndex() const { return C1Parser::RuleFuncfparams; }

void C1Parser::FuncfparamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncfparams(this);
}

void C1Parser::FuncfparamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncfparams(this);
}

antlrcpp::Any C1Parser::FuncfparamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitFuncfparams(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::FuncfparamsContext *C1Parser::funcfparams() {
  FuncfparamsContext *_localctx = _tracker.createInstance<FuncfparamsContext>(_ctx, getState());
  enterRule(_localctx, 22, C1Parser::RuleFuncfparams);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    funcfparam();
    setState(181);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C1Parser::Comma) {
      setState(177);
      match(C1Parser::Comma);
      setState(178);
      funcfparam();
      setState(183);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncfparamContext ------------------------------------------------------------------

C1Parser::FuncfparamContext::FuncfparamContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::FuncfparamContext::Int() { return getToken(C1Parser::Int, 0); }

tree::TerminalNode *C1Parser::FuncfparamContext::Identifier() { return getToken(C1Parser::Identifier, 0); }

std::vector<tree::TerminalNode *> C1Parser::FuncfparamContext::LeftBracket() {
  return getTokens(C1Parser::LeftBracket);
}

tree::TerminalNode *C1Parser::FuncfparamContext::LeftBracket(size_t i) { return getToken(C1Parser::LeftBracket, i); }

std::vector<tree::TerminalNode *> C1Parser::FuncfparamContext::RightBracket() {
  return getTokens(C1Parser::RightBracket);
}

tree::TerminalNode *C1Parser::FuncfparamContext::RightBracket(size_t i) { return getToken(C1Parser::RightBracket, i); }

std::vector<C1Parser::ExpContext *> C1Parser::FuncfparamContext::exp() {
  return getRuleContexts<C1Parser::ExpContext>();
}

C1Parser::ExpContext *C1Parser::FuncfparamContext::exp(size_t i) { return getRuleContext<C1Parser::ExpContext>(i); }

size_t C1Parser::FuncfparamContext::getRuleIndex() const { return C1Parser::RuleFuncfparam; }

void C1Parser::FuncfparamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncfparam(this);
}

void C1Parser::FuncfparamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncfparam(this);
}

antlrcpp::Any C1Parser::FuncfparamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitFuncfparam(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::FuncfparamContext *C1Parser::funcfparam() {
  FuncfparamContext *_localctx = _tracker.createInstance<FuncfparamContext>(_ctx, getState());
  enterRule(_localctx, 24, C1Parser::RuleFuncfparam);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    match(C1Parser::Int);
    setState(185);
    match(C1Parser::Identifier);
    setState(197);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C1Parser::LeftBracket) {
      setState(186);
      match(C1Parser::LeftBracket);
      setState(187);
      match(C1Parser::RightBracket);
      setState(194);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C1Parser::LeftBracket) {
        setState(188);
        match(C1Parser::LeftBracket);
        setState(189);
        exp();
        setState(190);
        match(C1Parser::RightBracket);
        setState(196);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctypeContext ------------------------------------------------------------------

C1Parser::FunctypeContext::FunctypeContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::FunctypeContext::Void() { return getToken(C1Parser::Void, 0); }

tree::TerminalNode *C1Parser::FunctypeContext::Int() { return getToken(C1Parser::Int, 0); }

size_t C1Parser::FunctypeContext::getRuleIndex() const { return C1Parser::RuleFunctype; }

void C1Parser::FunctypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctype(this);
}

void C1Parser::FunctypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctype(this);
}

antlrcpp::Any C1Parser::FunctypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitFunctype(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::FunctypeContext *C1Parser::functype() {
  FunctypeContext *_localctx = _tracker.createInstance<FunctypeContext>(_ctx, getState());
  enterRule(_localctx, 26, C1Parser::RuleFunctype);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    _la = _input->LA(1);
    if (!(_la == C1Parser::Int

          || _la == C1Parser::Void)) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

C1Parser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::BlockContext::LeftBrace() { return getToken(C1Parser::LeftBrace, 0); }

tree::TerminalNode *C1Parser::BlockContext::RightBrace() { return getToken(C1Parser::RightBrace, 0); }

std::vector<C1Parser::BlockbodyContext *> C1Parser::BlockContext::blockbody() {
  return getRuleContexts<C1Parser::BlockbodyContext>();
}

C1Parser::BlockbodyContext *C1Parser::BlockContext::blockbody(size_t i) {
  return getRuleContext<C1Parser::BlockbodyContext>(i);
}

size_t C1Parser::BlockContext::getRuleIndex() const { return C1Parser::RuleBlock; }

void C1Parser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void C1Parser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}

antlrcpp::Any C1Parser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::BlockContext *C1Parser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 28, C1Parser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    match(C1Parser::LeftBrace);
    setState(205);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~0x3fULL) == 0) &&
            ((1ULL << _la) &
             ((1ULL << C1Parser::SemiColon) | (1ULL << C1Parser::LeftBrace) | (1ULL << C1Parser::LeftParen) |
              (1ULL << C1Parser::If) | (1ULL << C1Parser::While) | (1ULL << C1Parser::Break) |
              (1ULL << C1Parser::Continue) | (1ULL << C1Parser::Return) | (1ULL << C1Parser::Const) |
              (1ULL << C1Parser::Negative) | (1ULL << C1Parser::Plus) | (1ULL << C1Parser::Minus) |
              (1ULL << C1Parser::Int) | (1ULL << C1Parser::Identifier) | (1ULL << C1Parser::IntConst))) != 0)) {
      setState(202);
      blockbody();
      setState(207);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(208);
    match(C1Parser::RightBrace);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockbodyContext ------------------------------------------------------------------

C1Parser::BlockbodyContext::BlockbodyContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::DeclContext *C1Parser::BlockbodyContext::decl() { return getRuleContext<C1Parser::DeclContext>(0); }

C1Parser::StmtContext *C1Parser::BlockbodyContext::stmt() { return getRuleContext<C1Parser::StmtContext>(0); }

size_t C1Parser::BlockbodyContext::getRuleIndex() const { return C1Parser::RuleBlockbody; }

void C1Parser::BlockbodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockbody(this);
}

void C1Parser::BlockbodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockbody(this);
}

antlrcpp::Any C1Parser::BlockbodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitBlockbody(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::BlockbodyContext *C1Parser::blockbody() {
  BlockbodyContext *_localctx = _tracker.createInstance<BlockbodyContext>(_ctx, getState());
  enterRule(_localctx, 30, C1Parser::RuleBlockbody);

  auto onExit = finally([=] { exitRule(); });
  try {
    setState(212);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case C1Parser::Const:
    case C1Parser::Int: {
      enterOuterAlt(_localctx, 1);
      setState(210);
      decl();
      break;
    }

    case C1Parser::SemiColon:
    case C1Parser::LeftBrace:
    case C1Parser::LeftParen:
    case C1Parser::If:
    case C1Parser::While:
    case C1Parser::Break:
    case C1Parser::Continue:
    case C1Parser::Return:
    case C1Parser::Negative:
    case C1Parser::Plus:
    case C1Parser::Minus:
    case C1Parser::Identifier:
    case C1Parser::IntConst: {
      enterOuterAlt(_localctx, 2);
      setState(211);
      stmt();
      break;
    }

    default:
      throw NoViableAltException(this);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

C1Parser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::LvalContext *C1Parser::StmtContext::lval() { return getRuleContext<C1Parser::LvalContext>(0); }

tree::TerminalNode *C1Parser::StmtContext::Assign() { return getToken(C1Parser::Assign, 0); }

C1Parser::ExpContext *C1Parser::StmtContext::exp() { return getRuleContext<C1Parser::ExpContext>(0); }

tree::TerminalNode *C1Parser::StmtContext::SemiColon() { return getToken(C1Parser::SemiColon, 0); }

C1Parser::BlockContext *C1Parser::StmtContext::block() { return getRuleContext<C1Parser::BlockContext>(0); }

tree::TerminalNode *C1Parser::StmtContext::If() { return getToken(C1Parser::If, 0); }

tree::TerminalNode *C1Parser::StmtContext::LeftParen() { return getToken(C1Parser::LeftParen, 0); }

C1Parser::CondContext *C1Parser::StmtContext::cond() { return getRuleContext<C1Parser::CondContext>(0); }

tree::TerminalNode *C1Parser::StmtContext::RightParen() { return getToken(C1Parser::RightParen, 0); }

std::vector<C1Parser::StmtContext *> C1Parser::StmtContext::stmt() { return getRuleContexts<C1Parser::StmtContext>(); }

C1Parser::StmtContext *C1Parser::StmtContext::stmt(size_t i) { return getRuleContext<C1Parser::StmtContext>(i); }

tree::TerminalNode *C1Parser::StmtContext::Else() { return getToken(C1Parser::Else, 0); }

tree::TerminalNode *C1Parser::StmtContext::While() { return getToken(C1Parser::While, 0); }

tree::TerminalNode *C1Parser::StmtContext::Break() { return getToken(C1Parser::Break, 0); }

tree::TerminalNode *C1Parser::StmtContext::Continue() { return getToken(C1Parser::Continue, 0); }

tree::TerminalNode *C1Parser::StmtContext::Return() { return getToken(C1Parser::Return, 0); }

size_t C1Parser::StmtContext::getRuleIndex() const { return C1Parser::RuleStmt; }

void C1Parser::StmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt(this);
}

void C1Parser::StmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt(this);
}

antlrcpp::Any C1Parser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::StmtContext *C1Parser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 32, C1Parser::RuleStmt);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    setState(248);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(214);
      lval();
      setState(215);
      match(C1Parser::Assign);
      setState(216);
      exp();
      setState(217);
      match(C1Parser::SemiColon);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(220);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) &
            ((1ULL << C1Parser::LeftParen) | (1ULL << C1Parser::Negative) | (1ULL << C1Parser::Plus) |
             (1ULL << C1Parser::Minus) | (1ULL << C1Parser::Identifier) | (1ULL << C1Parser::IntConst))) != 0)) {
        setState(219);
        exp();
      }
      setState(222);
      match(C1Parser::SemiColon);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(223);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(224);
      match(C1Parser::If);
      setState(225);
      match(C1Parser::LeftParen);
      setState(226);
      cond();
      setState(227);
      match(C1Parser::RightParen);
      setState(228);
      stmt();
      setState(231);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(229);
        match(C1Parser::Else);
        setState(230);
        stmt();
        break;
      }
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(233);
      match(C1Parser::While);
      setState(234);
      match(C1Parser::LeftParen);
      setState(235);
      cond();
      setState(236);
      match(C1Parser::RightParen);
      setState(237);
      stmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(239);
      match(C1Parser::Break);
      setState(240);
      match(C1Parser::SemiColon);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(241);
      match(C1Parser::Continue);
      setState(242);
      match(C1Parser::SemiColon);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(243);
      match(C1Parser::Return);
      setState(245);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) &
            ((1ULL << C1Parser::LeftParen) | (1ULL << C1Parser::Negative) | (1ULL << C1Parser::Plus) |
             (1ULL << C1Parser::Minus) | (1ULL << C1Parser::Identifier) | (1ULL << C1Parser::IntConst))) != 0)) {
        setState(244);
        exp();
      }
      setState(247);
      match(C1Parser::SemiColon);
      break;
    }
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

C1Parser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::AddexpContext *C1Parser::ExpContext::addexp() { return getRuleContext<C1Parser::AddexpContext>(0); }

size_t C1Parser::ExpContext::getRuleIndex() const { return C1Parser::RuleExp; }

void C1Parser::ExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExp(this);
}

void C1Parser::ExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExp(this);
}

antlrcpp::Any C1Parser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::ExpContext *C1Parser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 34, C1Parser::RuleExp);

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(250);
    addexp(0);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

C1Parser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::LorexpContext *C1Parser::CondContext::lorexp() { return getRuleContext<C1Parser::LorexpContext>(0); }

size_t C1Parser::CondContext::getRuleIndex() const { return C1Parser::RuleCond; }

void C1Parser::CondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCond(this);
}

void C1Parser::CondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCond(this);
}

antlrcpp::Any C1Parser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::CondContext *C1Parser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 36, C1Parser::RuleCond);

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    lorexp(0);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LvalContext ------------------------------------------------------------------

C1Parser::LvalContext::LvalContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::LvalContext::Identifier() { return getToken(C1Parser::Identifier, 0); }

std::vector<tree::TerminalNode *> C1Parser::LvalContext::LeftBracket() { return getTokens(C1Parser::LeftBracket); }

tree::TerminalNode *C1Parser::LvalContext::LeftBracket(size_t i) { return getToken(C1Parser::LeftBracket, i); }

std::vector<C1Parser::ExpContext *> C1Parser::LvalContext::exp() { return getRuleContexts<C1Parser::ExpContext>(); }

C1Parser::ExpContext *C1Parser::LvalContext::exp(size_t i) { return getRuleContext<C1Parser::ExpContext>(i); }

std::vector<tree::TerminalNode *> C1Parser::LvalContext::RightBracket() { return getTokens(C1Parser::RightBracket); }

tree::TerminalNode *C1Parser::LvalContext::RightBracket(size_t i) { return getToken(C1Parser::RightBracket, i); }

size_t C1Parser::LvalContext::getRuleIndex() const { return C1Parser::RuleLval; }

void C1Parser::LvalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLval(this);
}

void C1Parser::LvalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLval(this);
}

antlrcpp::Any C1Parser::LvalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitLval(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::LvalContext *C1Parser::lval() {
  LvalContext *_localctx = _tracker.createInstance<LvalContext>(_ctx, getState());
  enterRule(_localctx, 38, C1Parser::RuleLval);

  auto onExit = finally([=] { exitRule(); });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(254);
    match(C1Parser::Identifier);
    setState(261);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(255);
        match(C1Parser::LeftBracket);
        setState(256);
        exp();
        setState(257);
        match(C1Parser::RightBracket);
      }
      setState(263);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryexpContext ------------------------------------------------------------------

C1Parser::PrimaryexpContext::PrimaryexpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::PrimaryexpContext::LeftParen() { return getToken(C1Parser::LeftParen, 0); }

C1Parser::ExpContext *C1Parser::PrimaryexpContext::exp() { return getRuleContext<C1Parser::ExpContext>(0); }

tree::TerminalNode *C1Parser::PrimaryexpContext::RightParen() { return getToken(C1Parser::RightParen, 0); }

C1Parser::LvalContext *C1Parser::PrimaryexpContext::lval() { return getRuleContext<C1Parser::LvalContext>(0); }

C1Parser::NumberContext *C1Parser::PrimaryexpContext::number() { return getRuleContext<C1Parser::NumberContext>(0); }

size_t C1Parser::PrimaryexpContext::getRuleIndex() const { return C1Parser::RulePrimaryexp; }

void C1Parser::PrimaryexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryexp(this);
}

void C1Parser::PrimaryexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryexp(this);
}

antlrcpp::Any C1Parser::PrimaryexpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitPrimaryexp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::PrimaryexpContext *C1Parser::primaryexp() {
  PrimaryexpContext *_localctx = _tracker.createInstance<PrimaryexpContext>(_ctx, getState());
  enterRule(_localctx, 40, C1Parser::RulePrimaryexp);

  auto onExit = finally([=] { exitRule(); });
  try {
    setState(270);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case C1Parser::LeftParen: {
      enterOuterAlt(_localctx, 1);
      setState(264);
      match(C1Parser::LeftParen);
      setState(265);
      exp();
      setState(266);
      match(C1Parser::RightParen);
      break;
    }

    case C1Parser::Identifier: {
      enterOuterAlt(_localctx, 2);
      setState(268);
      lval();
      break;
    }

    case C1Parser::IntConst: {
      enterOuterAlt(_localctx, 3);
      setState(269);
      number();
      break;
    }

    default:
      throw NoViableAltException(this);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryexpContext ------------------------------------------------------------------

C1Parser::UnaryexpContext::UnaryexpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::PrimaryexpContext *C1Parser::UnaryexpContext::primaryexp() {
  return getRuleContext<C1Parser::PrimaryexpContext>(0);
}

tree::TerminalNode *C1Parser::UnaryexpContext::Identifier() { return getToken(C1Parser::Identifier, 0); }

tree::TerminalNode *C1Parser::UnaryexpContext::LeftParen() { return getToken(C1Parser::LeftParen, 0); }

tree::TerminalNode *C1Parser::UnaryexpContext::RightParen() { return getToken(C1Parser::RightParen, 0); }

C1Parser::FuncrparamsContext *C1Parser::UnaryexpContext::funcrparams() {
  return getRuleContext<C1Parser::FuncrparamsContext>(0);
}

C1Parser::UnaryopContext *C1Parser::UnaryexpContext::unaryop() { return getRuleContext<C1Parser::UnaryopContext>(0); }

C1Parser::UnaryexpContext *C1Parser::UnaryexpContext::unaryexp() {
  return getRuleContext<C1Parser::UnaryexpContext>(0);
}

size_t C1Parser::UnaryexpContext::getRuleIndex() const { return C1Parser::RuleUnaryexp; }

void C1Parser::UnaryexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryexp(this);
}

void C1Parser::UnaryexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryexp(this);
}

antlrcpp::Any C1Parser::UnaryexpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitUnaryexp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::UnaryexpContext *C1Parser::unaryexp() {
  UnaryexpContext *_localctx = _tracker.createInstance<UnaryexpContext>(_ctx, getState());
  enterRule(_localctx, 42, C1Parser::RuleUnaryexp);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    setState(282);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(272);
      primaryexp();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(273);
      match(C1Parser::Identifier);
      setState(274);
      match(C1Parser::LeftParen);
      setState(276);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) &
            ((1ULL << C1Parser::LeftParen) | (1ULL << C1Parser::Negative) | (1ULL << C1Parser::Plus) |
             (1ULL << C1Parser::Minus) | (1ULL << C1Parser::Identifier) | (1ULL << C1Parser::IntConst))) != 0)) {
        setState(275);
        funcrparams();
      }
      setState(278);
      match(C1Parser::RightParen);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(279);
      unaryop();
      setState(280);
      unaryexp();
      break;
    }
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryopContext ------------------------------------------------------------------

C1Parser::UnaryopContext::UnaryopContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::UnaryopContext::Plus() { return getToken(C1Parser::Plus, 0); }

tree::TerminalNode *C1Parser::UnaryopContext::Minus() { return getToken(C1Parser::Minus, 0); }

tree::TerminalNode *C1Parser::UnaryopContext::Negative() { return getToken(C1Parser::Negative, 0); }

size_t C1Parser::UnaryopContext::getRuleIndex() const { return C1Parser::RuleUnaryop; }

void C1Parser::UnaryopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryop(this);
}

void C1Parser::UnaryopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryop(this);
}

antlrcpp::Any C1Parser::UnaryopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitUnaryop(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::UnaryopContext *C1Parser::unaryop() {
  UnaryopContext *_localctx = _tracker.createInstance<UnaryopContext>(_ctx, getState());
  enterRule(_localctx, 44, C1Parser::RuleUnaryop);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(284);
    _la = _input->LA(1);
    if (!((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & ((1ULL << C1Parser::Negative) | (1ULL << C1Parser::Plus) |
                                                        (1ULL << C1Parser::Minus))) != 0))) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncrparamsContext ------------------------------------------------------------------

C1Parser::FuncrparamsContext::FuncrparamsContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<C1Parser::ExpContext *> C1Parser::FuncrparamsContext::exp() {
  return getRuleContexts<C1Parser::ExpContext>();
}

C1Parser::ExpContext *C1Parser::FuncrparamsContext::exp(size_t i) { return getRuleContext<C1Parser::ExpContext>(i); }

std::vector<tree::TerminalNode *> C1Parser::FuncrparamsContext::Comma() { return getTokens(C1Parser::Comma); }

tree::TerminalNode *C1Parser::FuncrparamsContext::Comma(size_t i) { return getToken(C1Parser::Comma, i); }

size_t C1Parser::FuncrparamsContext::getRuleIndex() const { return C1Parser::RuleFuncrparams; }

void C1Parser::FuncrparamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncrparams(this);
}

void C1Parser::FuncrparamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncrparams(this);
}

antlrcpp::Any C1Parser::FuncrparamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitFuncrparams(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::FuncrparamsContext *C1Parser::funcrparams() {
  FuncrparamsContext *_localctx = _tracker.createInstance<FuncrparamsContext>(_ctx, getState());
  enterRule(_localctx, 46, C1Parser::RuleFuncrparams);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(286);
    exp();
    setState(291);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C1Parser::Comma) {
      setState(287);
      match(C1Parser::Comma);
      setState(288);
      exp();
      setState(293);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulexpContext ------------------------------------------------------------------

C1Parser::MulexpContext::MulexpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::UnaryexpContext *C1Parser::MulexpContext::unaryexp() { return getRuleContext<C1Parser::UnaryexpContext>(0); }

C1Parser::MulexpContext *C1Parser::MulexpContext::mulexp() { return getRuleContext<C1Parser::MulexpContext>(0); }

tree::TerminalNode *C1Parser::MulexpContext::Multiply() { return getToken(C1Parser::Multiply, 0); }

tree::TerminalNode *C1Parser::MulexpContext::Divide() { return getToken(C1Parser::Divide, 0); }

tree::TerminalNode *C1Parser::MulexpContext::Modulo() { return getToken(C1Parser::Modulo, 0); }

size_t C1Parser::MulexpContext::getRuleIndex() const { return C1Parser::RuleMulexp; }

void C1Parser::MulexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulexp(this);
}

void C1Parser::MulexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulexp(this);
}

antlrcpp::Any C1Parser::MulexpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitMulexp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::MulexpContext *C1Parser::mulexp() { return mulexp(0); }

C1Parser::MulexpContext *C1Parser::mulexp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C1Parser::MulexpContext *_localctx = _tracker.createInstance<MulexpContext>(_ctx, parentState);
  C1Parser::MulexpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, C1Parser::RuleMulexp, precedence);

  size_t _la = 0;

  auto onExit = finally([=] { unrollRecursionContexts(parentContext); });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(295);
    unaryexp();
    _ctx->stop = _input->LT(-1);
    setState(302);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<MulexpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMulexp);
        setState(297);

        if (!(precpred(_ctx, 1)))
          throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(298);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & ((1ULL << C1Parser::Multiply) | (1ULL << C1Parser::Divide) |
                                                            (1ULL << C1Parser::Modulo))) != 0))) {
          _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(299);
        unaryexp();
      }
      setState(304);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AddexpContext ------------------------------------------------------------------

C1Parser::AddexpContext::AddexpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::MulexpContext *C1Parser::AddexpContext::mulexp() { return getRuleContext<C1Parser::MulexpContext>(0); }

C1Parser::AddexpContext *C1Parser::AddexpContext::addexp() { return getRuleContext<C1Parser::AddexpContext>(0); }

tree::TerminalNode *C1Parser::AddexpContext::Plus() { return getToken(C1Parser::Plus, 0); }

tree::TerminalNode *C1Parser::AddexpContext::Minus() { return getToken(C1Parser::Minus, 0); }

size_t C1Parser::AddexpContext::getRuleIndex() const { return C1Parser::RuleAddexp; }

void C1Parser::AddexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddexp(this);
}

void C1Parser::AddexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddexp(this);
}

antlrcpp::Any C1Parser::AddexpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitAddexp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::AddexpContext *C1Parser::addexp() { return addexp(0); }

C1Parser::AddexpContext *C1Parser::addexp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C1Parser::AddexpContext *_localctx = _tracker.createInstance<AddexpContext>(_ctx, parentState);
  C1Parser::AddexpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, C1Parser::RuleAddexp, precedence);

  size_t _la = 0;

  auto onExit = finally([=] { unrollRecursionContexts(parentContext); });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(306);
    mulexp(0);
    _ctx->stop = _input->LT(-1);
    setState(313);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<AddexpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAddexp);
        setState(308);

        if (!(precpred(_ctx, 1)))
          throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(309);
        _la = _input->LA(1);
        if (!(_la == C1Parser::Plus

              || _la == C1Parser::Minus)) {
          _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(310);
        mulexp(0);
      }
      setState(315);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RelexpContext ------------------------------------------------------------------

C1Parser::RelexpContext::RelexpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::AddexpContext *C1Parser::RelexpContext::addexp() { return getRuleContext<C1Parser::AddexpContext>(0); }

C1Parser::RelexpContext *C1Parser::RelexpContext::relexp() { return getRuleContext<C1Parser::RelexpContext>(0); }

tree::TerminalNode *C1Parser::RelexpContext::Less() { return getToken(C1Parser::Less, 0); }

tree::TerminalNode *C1Parser::RelexpContext::Greater() { return getToken(C1Parser::Greater, 0); }

tree::TerminalNode *C1Parser::RelexpContext::LessEqual() { return getToken(C1Parser::LessEqual, 0); }

tree::TerminalNode *C1Parser::RelexpContext::GreaterEqual() { return getToken(C1Parser::GreaterEqual, 0); }

size_t C1Parser::RelexpContext::getRuleIndex() const { return C1Parser::RuleRelexp; }

void C1Parser::RelexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelexp(this);
}

void C1Parser::RelexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelexp(this);
}

antlrcpp::Any C1Parser::RelexpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitRelexp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::RelexpContext *C1Parser::relexp() { return relexp(0); }

C1Parser::RelexpContext *C1Parser::relexp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C1Parser::RelexpContext *_localctx = _tracker.createInstance<RelexpContext>(_ctx, parentState);
  C1Parser::RelexpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, C1Parser::RuleRelexp, precedence);

  size_t _la = 0;

  auto onExit = finally([=] { unrollRecursionContexts(parentContext); });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(317);
    addexp(0);
    _ctx->stop = _input->LT(-1);
    setState(324);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<RelexpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleRelexp);
        setState(319);

        if (!(precpred(_ctx, 1)))
          throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(320);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0) &&
               ((1ULL << _la) & ((1ULL << C1Parser::Less) | (1ULL << C1Parser::Greater) |
                                 (1ULL << C1Parser::LessEqual) | (1ULL << C1Parser::GreaterEqual))) != 0))) {
          _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(321);
        addexp(0);
      }
      setState(326);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EqexpContext ------------------------------------------------------------------

C1Parser::EqexpContext::EqexpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::RelexpContext *C1Parser::EqexpContext::relexp() { return getRuleContext<C1Parser::RelexpContext>(0); }

C1Parser::EqexpContext *C1Parser::EqexpContext::eqexp() { return getRuleContext<C1Parser::EqexpContext>(0); }

tree::TerminalNode *C1Parser::EqexpContext::Equal() { return getToken(C1Parser::Equal, 0); }

tree::TerminalNode *C1Parser::EqexpContext::NonEqual() { return getToken(C1Parser::NonEqual, 0); }

size_t C1Parser::EqexpContext::getRuleIndex() const { return C1Parser::RuleEqexp; }

void C1Parser::EqexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqexp(this);
}

void C1Parser::EqexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqexp(this);
}

antlrcpp::Any C1Parser::EqexpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitEqexp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::EqexpContext *C1Parser::eqexp() { return eqexp(0); }

C1Parser::EqexpContext *C1Parser::eqexp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C1Parser::EqexpContext *_localctx = _tracker.createInstance<EqexpContext>(_ctx, parentState);
  C1Parser::EqexpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, C1Parser::RuleEqexp, precedence);

  size_t _la = 0;

  auto onExit = finally([=] { unrollRecursionContexts(parentContext); });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(328);
    relexp(0);
    _ctx->stop = _input->LT(-1);
    setState(335);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<EqexpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleEqexp);
        setState(330);

        if (!(precpred(_ctx, 1)))
          throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(331);
        _la = _input->LA(1);
        if (!(_la == C1Parser::Equal

              || _la == C1Parser::NonEqual)) {
          _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(332);
        relexp(0);
      }
      setState(337);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LandexpContext ------------------------------------------------------------------

C1Parser::LandexpContext::LandexpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::EqexpContext *C1Parser::LandexpContext::eqexp() { return getRuleContext<C1Parser::EqexpContext>(0); }

C1Parser::LandexpContext *C1Parser::LandexpContext::landexp() { return getRuleContext<C1Parser::LandexpContext>(0); }

tree::TerminalNode *C1Parser::LandexpContext::LogicalAnd() { return getToken(C1Parser::LogicalAnd, 0); }

size_t C1Parser::LandexpContext::getRuleIndex() const { return C1Parser::RuleLandexp; }

void C1Parser::LandexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLandexp(this);
}

void C1Parser::LandexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLandexp(this);
}

antlrcpp::Any C1Parser::LandexpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitLandexp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::LandexpContext *C1Parser::landexp() { return landexp(0); }

C1Parser::LandexpContext *C1Parser::landexp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C1Parser::LandexpContext *_localctx = _tracker.createInstance<LandexpContext>(_ctx, parentState);
  C1Parser::LandexpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, C1Parser::RuleLandexp, precedence);

  auto onExit = finally([=] { unrollRecursionContexts(parentContext); });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(339);
    eqexp(0);
    _ctx->stop = _input->LT(-1);
    setState(346);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LandexpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLandexp);
        setState(341);

        if (!(precpred(_ctx, 1)))
          throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(342);
        match(C1Parser::LogicalAnd);
        setState(343);
        eqexp(0);
      }
      setState(348);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LorexpContext ------------------------------------------------------------------

C1Parser::LorexpContext::LorexpContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

C1Parser::LandexpContext *C1Parser::LorexpContext::landexp() { return getRuleContext<C1Parser::LandexpContext>(0); }

C1Parser::LorexpContext *C1Parser::LorexpContext::lorexp() { return getRuleContext<C1Parser::LorexpContext>(0); }

tree::TerminalNode *C1Parser::LorexpContext::LogicalOr() { return getToken(C1Parser::LogicalOr, 0); }

size_t C1Parser::LorexpContext::getRuleIndex() const { return C1Parser::RuleLorexp; }

void C1Parser::LorexpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLorexp(this);
}

void C1Parser::LorexpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLorexp(this);
}

antlrcpp::Any C1Parser::LorexpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitLorexp(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::LorexpContext *C1Parser::lorexp() { return lorexp(0); }

C1Parser::LorexpContext *C1Parser::lorexp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C1Parser::LorexpContext *_localctx = _tracker.createInstance<LorexpContext>(_ctx, parentState);
  C1Parser::LorexpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, C1Parser::RuleLorexp, precedence);

  auto onExit = finally([=] { unrollRecursionContexts(parentContext); });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(350);
    landexp(0);
    _ctx->stop = _input->LT(-1);
    setState(357);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<LorexpContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLorexp);
        setState(352);

        if (!(precpred(_ctx, 1)))
          throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(353);
        match(C1Parser::LogicalOr);
        setState(354);
        landexp(0);
      }
      setState(359);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

C1Parser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *C1Parser::NumberContext::IntConst() { return getToken(C1Parser::IntConst, 0); }

size_t C1Parser::NumberContext::getRuleIndex() const { return C1Parser::RuleNumber; }

void C1Parser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void C1Parser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C1ParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

antlrcpp::Any C1Parser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C1ParserVisitor *>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

C1Parser::NumberContext *C1Parser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 60, C1Parser::RuleNumber);

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(360);
    match(C1Parser::IntConst);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool C1Parser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
  case 24:
    return mulexpSempred(dynamic_cast<MulexpContext *>(context), predicateIndex);
  case 25:
    return addexpSempred(dynamic_cast<AddexpContext *>(context), predicateIndex);
  case 26:
    return relexpSempred(dynamic_cast<RelexpContext *>(context), predicateIndex);
  case 27:
    return eqexpSempred(dynamic_cast<EqexpContext *>(context), predicateIndex);
  case 28:
    return landexpSempred(dynamic_cast<LandexpContext *>(context), predicateIndex);
  case 29:
    return lorexpSempred(dynamic_cast<LorexpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool C1Parser::mulexpSempred(MulexpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
  case 0:
    return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C1Parser::addexpSempred(AddexpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
  case 1:
    return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C1Parser::relexpSempred(RelexpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
  case 2:
    return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C1Parser::eqexpSempred(EqexpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
  case 3:
    return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C1Parser::landexpSempred(LandexpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
  case 4:
    return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool C1Parser::lorexpSempred(LorexpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
  case 5:
    return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> C1Parser::_decisionToDFA;
atn::PredictionContextCache C1Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN C1Parser::_atn;
std::vector<uint16_t> C1Parser::_serializedATN;

std::vector<std::string> C1Parser::_ruleNames = {
    "compilationUnit", "start",     "decl",        "constdecl", "constdef",    "constinitval", "constexp",
    "vardecl",         "vardef",    "initval",     "funcdef",   "funcfparams", "funcfparam",   "functype",
    "block",           "blockbody", "stmt",        "exp",       "cond",        "lval",         "primaryexp",
    "unaryexp",        "unaryop",   "funcrparams", "mulexp",    "addexp",      "relexp",       "eqexp",
    "landexp",         "lorexp",    "number"};

std::vector<std::string> C1Parser::_literalNames = {
    "",       "','",     "';'",     "'='",        "'['",      "']'",     "'{'",  "'}'",  "'('", "')'",   "'if'",
    "'else'", "'while'", "'break'", "'continue'", "'return'", "'const'", "'=='", "'!='", "'!'", "'&&'",  "'||'",
    "'<'",    "'>'",     "'<='",    "'>='",       "'+'",      "'-'",     "'*'",  "'/'",  "'%'", "'int'", "'void'"};

std::vector<std::string> C1Parser::_symbolicNames = {
    "",          "Comma",        "SemiColon", "Assign",      "LeftBracket",  "RightBracket", "LeftBrace", "RightBrace",
    "LeftParen", "RightParen",   "If",        "Else",        "While",        "Break",        "Continue",  "Return",
    "Const",     "Equal",        "NonEqual",  "Negative",    "LogicalAnd",   "LogicalOr",    "Less",      "Greater",
    "LessEqual", "GreaterEqual", "Plus",      "Minus",       "Multiply",     "Divide",       "Modulo",    "Int",
    "Void",      "Identifier",   "IntConst",  "LineComment", "BlockComment", "WhiteSpace"};

dfa::Vocabulary C1Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> C1Parser::_tokenNames;

C1Parser::Initializer::Initializer() {
  for (size_t i = 0; i < _symbolicNames.size(); ++i) {
    std::string name = _vocabulary.getLiteralName(i);
    if (name.empty()) {
      name = _vocabulary.getSymbolicName(i);
    }

    if (name.empty()) {
      _tokenNames.push_back("<INVALID>");
    } else {
      _tokenNames.push_back(name);
    }
  }

  _serializedATN = {
      0x3,   0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 0x3,   0x27,  0x16d, 0x4,   0x2,   0x9,
      0x2,   0x4,    0x3,    0x9,    0x3,    0x4,    0x4,    0x9,    0x4,    0x4,   0x5,   0x9,   0x5,   0x4,   0x6,
      0x9,   0x6,    0x4,    0x7,    0x9,    0x7,    0x4,    0x8,    0x9,    0x8,   0x4,   0x9,   0x9,   0x9,   0x4,
      0xa,   0x9,    0xa,    0x4,    0xb,    0x9,    0xb,    0x4,    0xc,    0x9,   0xc,   0x4,   0xd,   0x9,   0xd,
      0x4,   0xe,    0x9,    0xe,    0x4,    0xf,    0x9,    0xf,    0x4,    0x10,  0x9,   0x10,  0x4,   0x11,  0x9,
      0x11,  0x4,    0x12,   0x9,    0x12,   0x4,    0x13,   0x9,    0x13,   0x4,   0x14,  0x9,   0x14,  0x4,   0x15,
      0x9,   0x15,   0x4,    0x16,   0x9,    0x16,   0x4,    0x17,   0x9,    0x17,  0x4,   0x18,  0x9,   0x18,  0x4,
      0x19,  0x9,    0x19,   0x4,    0x1a,   0x9,    0x1a,   0x4,    0x1b,   0x9,   0x1b,  0x4,   0x1c,  0x9,   0x1c,
      0x4,   0x1d,   0x9,    0x1d,   0x4,    0x1e,   0x9,    0x1e,   0x4,    0x1f,  0x9,   0x1f,  0x4,   0x20,  0x9,
      0x20,  0x3,    0x2,    0x6,    0x2,    0x42,   0xa,    0x2,    0xd,    0x2,   0xe,   0x2,   0x43,  0x3,   0x3,
      0x3,   0x3,    0x5,    0x3,    0x48,   0xa,    0x3,    0x3,    0x4,    0x3,   0x4,   0x5,   0x4,   0x4c,  0xa,
      0x4,   0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,   0x5,   0x7,   0x5,   0x53,  0xa,
      0x5,   0xc,    0x5,    0xe,    0x5,    0x56,   0xb,    0x5,    0x3,    0x5,   0x3,   0x5,   0x3,   0x6,   0x3,
      0x6,   0x3,    0x6,    0x3,    0x6,    0x3,    0x6,    0x7,    0x6,    0x5f,  0xa,   0x6,   0xc,   0x6,   0xe,
      0x6,   0x62,   0xb,    0x6,    0x3,    0x6,    0x3,    0x6,    0x3,    0x6,   0x3,   0x7,   0x3,   0x7,   0x3,
      0x7,   0x3,    0x7,    0x3,    0x7,    0x7,    0x7,    0x6c,   0xa,    0x7,   0xc,   0x7,   0xe,   0x7,   0x6f,
      0xb,   0x7,    0x5,    0x7,    0x71,   0xa,    0x7,    0x3,    0x7,    0x5,   0x7,   0x74,  0xa,   0x7,   0x3,
      0x8,   0x3,    0x8,    0x3,    0x9,    0x3,    0x9,    0x3,    0x9,    0x3,   0x9,   0x7,   0x9,   0x7c,  0xa,
      0x9,   0xc,    0x9,    0xe,    0x9,    0x7f,   0xb,    0x9,    0x3,    0x9,   0x3,   0x9,   0x3,   0xa,   0x3,
      0xa,   0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x7,    0xa,    0x88,  0xa,   0xa,   0xc,   0xa,   0xe,
      0xa,   0x8b,   0xb,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,   0x3,   0xa,   0x3,   0xa,   0x7,
      0xa,   0x92,   0xa,    0xa,    0xc,    0xa,    0xe,    0xa,    0x95,   0xb,   0xa,   0x3,   0xa,   0x3,   0xa,
      0x5,   0xa,    0x99,   0xa,    0xa,    0x3,    0xb,    0x3,    0xb,    0x3,   0xb,   0x3,   0xb,   0x3,   0xb,
      0x7,   0xb,    0xa0,   0xa,    0xb,    0xc,    0xb,    0xe,    0xb,    0xa3,  0xb,   0xb,   0x5,   0xb,   0xa5,
      0xa,   0xb,    0x3,    0xb,    0x5,    0xb,    0xa8,   0xa,    0xb,    0x3,   0xc,   0x3,   0xc,   0x3,   0xc,
      0x3,   0xc,    0x5,    0xc,    0xae,   0xa,    0xc,    0x3,    0xc,    0x3,   0xc,   0x3,   0xc,   0x3,   0xd,
      0x3,   0xd,    0x3,    0xd,    0x7,    0xd,    0xb6,   0xa,    0xd,    0xc,   0xd,   0xe,   0xd,   0xb9,  0xb,
      0xd,   0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,   0xe,   0x3,   0xe,   0x3,   0xe,
      0x3,   0xe,    0x7,    0xe,    0xc3,   0xa,    0xe,    0xc,    0xe,    0xe,   0xe,   0xc6,  0xb,   0xe,   0x5,
      0xe,   0xc8,   0xa,    0xe,    0x3,    0xf,    0x3,    0xf,    0x3,    0x10,  0x3,   0x10,  0x7,   0x10,  0xce,
      0xa,   0x10,   0xc,    0x10,   0xe,    0x10,   0xd1,   0xb,    0x10,   0x3,   0x10,  0x3,   0x10,  0x3,   0x11,
      0x3,   0x11,   0x5,    0x11,   0xd7,   0xa,    0x11,   0x3,    0x12,   0x3,   0x12,  0x3,   0x12,  0x3,   0x12,
      0x3,   0x12,   0x3,    0x12,   0x5,    0x12,   0xdf,   0xa,    0x12,   0x3,   0x12,  0x3,   0x12,  0x3,   0x12,
      0x3,   0x12,   0x3,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,    0x12,  0x3,   0x12,  0x5,   0x12,  0xea,
      0xa,   0x12,   0x3,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,    0x12,  0x3,   0x12,  0x3,   0x12,  0x3,
      0x12,  0x3,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,   0x12,  0x5,   0x12,  0xf8,  0xa,
      0x12,  0x3,    0x12,   0x5,    0x12,   0xfb,   0xa,    0x12,   0x3,    0x13,  0x3,   0x13,  0x3,   0x14,  0x3,
      0x14,  0x3,    0x15,   0x3,    0x15,   0x3,    0x15,   0x3,    0x15,   0x3,   0x15,  0x7,   0x15,  0x106, 0xa,
      0x15,  0xc,    0x15,   0xe,    0x15,   0x109,  0xb,    0x15,   0x3,    0x16,  0x3,   0x16,  0x3,   0x16,  0x3,
      0x16,  0x3,    0x16,   0x3,    0x16,   0x5,    0x16,   0x111,  0xa,    0x16,  0x3,   0x17,  0x3,   0x17,  0x3,
      0x17,  0x3,    0x17,   0x5,    0x17,   0x117,  0xa,    0x17,   0x3,    0x17,  0x3,   0x17,  0x3,   0x17,  0x3,
      0x17,  0x5,    0x17,   0x11d,  0xa,    0x17,   0x3,    0x18,   0x3,    0x18,  0x3,   0x19,  0x3,   0x19,  0x3,
      0x19,  0x7,    0x19,   0x124,  0xa,    0x19,   0xc,    0x19,   0xe,    0x19,  0x127, 0xb,   0x19,  0x3,   0x1a,
      0x3,   0x1a,   0x3,    0x1a,   0x3,    0x1a,   0x3,    0x1a,   0x3,    0x1a,  0x7,   0x1a,  0x12f, 0xa,   0x1a,
      0xc,   0x1a,   0xe,    0x1a,   0x132,  0xb,    0x1a,   0x3,    0x1b,   0x3,   0x1b,  0x3,   0x1b,  0x3,   0x1b,
      0x3,   0x1b,   0x3,    0x1b,   0x7,    0x1b,   0x13a,  0xa,    0x1b,   0xc,   0x1b,  0xe,   0x1b,  0x13d, 0xb,
      0x1b,  0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,    0x1c,   0x3,   0x1c,  0x3,   0x1c,  0x7,   0x1c,
      0x145, 0xa,    0x1c,   0xc,    0x1c,   0xe,    0x1c,   0x148,  0xb,    0x1c,  0x3,   0x1d,  0x3,   0x1d,  0x3,
      0x1d,  0x3,    0x1d,   0x3,    0x1d,   0x3,    0x1d,   0x7,    0x1d,   0x150, 0xa,   0x1d,  0xc,   0x1d,  0xe,
      0x1d,  0x153,  0xb,    0x1d,   0x3,    0x1e,   0x3,    0x1e,   0x3,    0x1e,  0x3,   0x1e,  0x3,   0x1e,  0x3,
      0x1e,  0x7,    0x1e,   0x15b,  0xa,    0x1e,   0xc,    0x1e,   0xe,    0x1e,  0x15e, 0xb,   0x1e,  0x3,   0x1f,
      0x3,   0x1f,   0x3,    0x1f,   0x3,    0x1f,   0x3,    0x1f,   0x3,    0x1f,  0x7,   0x1f,  0x166, 0xa,   0x1f,
      0xc,   0x1f,   0xe,    0x1f,   0x169,  0xb,    0x1f,   0x3,    0x20,   0x3,   0x20,  0x3,   0x20,  0x2,   0x8,
      0x32,  0x34,   0x36,   0x38,   0x3a,   0x3c,   0x21,   0x2,    0x4,    0x6,   0x8,   0xa,   0xc,   0xe,   0x10,
      0x12,  0x14,   0x16,   0x18,   0x1a,   0x1c,   0x1e,   0x20,   0x22,   0x24,  0x26,  0x28,  0x2a,  0x2c,  0x2e,
      0x30,  0x32,   0x34,   0x36,   0x38,   0x3a,   0x3c,   0x3e,   0x2,    0x8,   0x3,   0x2,   0x21,  0x22,  0x4,
      0x2,   0x15,   0x15,   0x1c,   0x1d,   0x3,    0x2,    0x1e,   0x20,   0x3,   0x2,   0x1c,  0x1d,  0x3,   0x2,
      0x18,  0x1b,   0x3,    0x2,    0x13,   0x14,   0x2,    0x179,  0x2,    0x41,  0x3,   0x2,   0x2,   0x2,   0x4,
      0x47,  0x3,    0x2,    0x2,    0x2,    0x6,    0x4b,   0x3,    0x2,    0x2,   0x2,   0x8,   0x4d,  0x3,   0x2,
      0x2,   0x2,    0xa,    0x59,   0x3,    0x2,    0x2,    0x2,    0xc,    0x73,  0x3,   0x2,   0x2,   0x2,   0xe,
      0x75,  0x3,    0x2,    0x2,    0x2,    0x10,   0x77,   0x3,    0x2,    0x2,   0x2,   0x12,  0x98,  0x3,   0x2,
      0x2,   0x2,    0x14,   0xa7,   0x3,    0x2,    0x2,    0x2,    0x16,   0xa9,  0x3,   0x2,   0x2,   0x2,   0x18,
      0xb2,  0x3,    0x2,    0x2,    0x2,    0x1a,   0xba,   0x3,    0x2,    0x2,   0x2,   0x1c,  0xc9,  0x3,   0x2,
      0x2,   0x2,    0x1e,   0xcb,   0x3,    0x2,    0x2,    0x2,    0x20,   0xd6,  0x3,   0x2,   0x2,   0x2,   0x22,
      0xfa,  0x3,    0x2,    0x2,    0x2,    0x24,   0xfc,   0x3,    0x2,    0x2,   0x2,   0x26,  0xfe,  0x3,   0x2,
      0x2,   0x2,    0x28,   0x100,  0x3,    0x2,    0x2,    0x2,    0x2a,   0x110, 0x3,   0x2,   0x2,   0x2,   0x2c,
      0x11c, 0x3,    0x2,    0x2,    0x2,    0x2e,   0x11e,  0x3,    0x2,    0x2,   0x2,   0x30,  0x120, 0x3,   0x2,
      0x2,   0x2,    0x32,   0x128,  0x3,    0x2,    0x2,    0x2,    0x34,   0x133, 0x3,   0x2,   0x2,   0x2,   0x36,
      0x13e, 0x3,    0x2,    0x2,    0x2,    0x38,   0x149,  0x3,    0x2,    0x2,   0x2,   0x3a,  0x154, 0x3,   0x2,
      0x2,   0x2,    0x3c,   0x15f,  0x3,    0x2,    0x2,    0x2,    0x3e,   0x16a, 0x3,   0x2,   0x2,   0x2,   0x40,
      0x42,  0x5,    0x4,    0x3,    0x2,    0x41,   0x40,   0x3,    0x2,    0x2,   0x2,   0x42,  0x43,  0x3,   0x2,
      0x2,   0x2,    0x43,   0x41,   0x3,    0x2,    0x2,    0x2,    0x43,   0x44,  0x3,   0x2,   0x2,   0x2,   0x44,
      0x3,   0x3,    0x2,    0x2,    0x2,    0x45,   0x48,   0x5,    0x6,    0x4,   0x2,   0x46,  0x48,  0x5,   0x16,
      0xc,   0x2,    0x47,   0x45,   0x3,    0x2,    0x2,    0x2,    0x47,   0x46,  0x3,   0x2,   0x2,   0x2,   0x48,
      0x5,   0x3,    0x2,    0x2,    0x2,    0x49,   0x4c,   0x5,    0x8,    0x5,   0x2,   0x4a,  0x4c,  0x5,   0x10,
      0x9,   0x2,    0x4b,   0x49,   0x3,    0x2,    0x2,    0x2,    0x4b,   0x4a,  0x3,   0x2,   0x2,   0x2,   0x4c,
      0x7,   0x3,    0x2,    0x2,    0x2,    0x4d,   0x4e,   0x7,    0x12,   0x2,   0x2,   0x4e,  0x4f,  0x7,   0x21,
      0x2,   0x2,    0x4f,   0x54,   0x5,    0xa,    0x6,    0x2,    0x50,   0x51,  0x7,   0x3,   0x2,   0x2,   0x51,
      0x53,  0x5,    0xa,    0x6,    0x2,    0x52,   0x50,   0x3,    0x2,    0x2,   0x2,   0x53,  0x56,  0x3,   0x2,
      0x2,   0x2,    0x54,   0x52,   0x3,    0x2,    0x2,    0x2,    0x54,   0x55,  0x3,   0x2,   0x2,   0x2,   0x55,
      0x57,  0x3,    0x2,    0x2,    0x2,    0x56,   0x54,   0x3,    0x2,    0x2,   0x2,   0x57,  0x58,  0x7,   0x4,
      0x2,   0x2,    0x58,   0x9,    0x3,    0x2,    0x2,    0x2,    0x59,   0x60,  0x7,   0x23,  0x2,   0x2,   0x5a,
      0x5b,  0x7,    0x6,    0x2,    0x2,    0x5b,   0x5c,   0x5,    0xe,    0x8,   0x2,   0x5c,  0x5d,  0x7,   0x7,
      0x2,   0x2,    0x5d,   0x5f,   0x3,    0x2,    0x2,    0x2,    0x5e,   0x5a,  0x3,   0x2,   0x2,   0x2,   0x5f,
      0x62,  0x3,    0x2,    0x2,    0x2,    0x60,   0x5e,   0x3,    0x2,    0x2,   0x2,   0x60,  0x61,  0x3,   0x2,
      0x2,   0x2,    0x61,   0x63,   0x3,    0x2,    0x2,    0x2,    0x62,   0x60,  0x3,   0x2,   0x2,   0x2,   0x63,
      0x64,  0x7,    0x5,    0x2,    0x2,    0x64,   0x65,   0x5,    0xc,    0x7,   0x2,   0x65,  0xb,   0x3,   0x2,
      0x2,   0x2,    0x66,   0x74,   0x5,    0xe,    0x8,    0x2,    0x67,   0x70,  0x7,   0x8,   0x2,   0x2,   0x68,
      0x6d,  0x5,    0xc,    0x7,    0x2,    0x69,   0x6a,   0x7,    0x3,    0x2,   0x2,   0x6a,  0x6c,  0x5,   0xc,
      0x7,   0x2,    0x6b,   0x69,   0x3,    0x2,    0x2,    0x2,    0x6c,   0x6f,  0x3,   0x2,   0x2,   0x2,   0x6d,
      0x6b,  0x3,    0x2,    0x2,    0x2,    0x6d,   0x6e,   0x3,    0x2,    0x2,   0x2,   0x6e,  0x71,  0x3,   0x2,
      0x2,   0x2,    0x6f,   0x6d,   0x3,    0x2,    0x2,    0x2,    0x70,   0x68,  0x3,   0x2,   0x2,   0x2,   0x70,
      0x71,  0x3,    0x2,    0x2,    0x2,    0x71,   0x72,   0x3,    0x2,    0x2,   0x2,   0x72,  0x74,  0x7,   0x9,
      0x2,   0x2,    0x73,   0x66,   0x3,    0x2,    0x2,    0x2,    0x73,   0x67,  0x3,   0x2,   0x2,   0x2,   0x74,
      0xd,   0x3,    0x2,    0x2,    0x2,    0x75,   0x76,   0x5,    0x34,   0x1b,  0x2,   0x76,  0xf,   0x3,   0x2,
      0x2,   0x2,    0x77,   0x78,   0x7,    0x21,   0x2,    0x2,    0x78,   0x7d,  0x5,   0x12,  0xa,   0x2,   0x79,
      0x7a,  0x7,    0x3,    0x2,    0x2,    0x7a,   0x7c,   0x5,    0x12,   0xa,   0x2,   0x7b,  0x79,  0x3,   0x2,
      0x2,   0x2,    0x7c,   0x7f,   0x3,    0x2,    0x2,    0x2,    0x7d,   0x7b,  0x3,   0x2,   0x2,   0x2,   0x7d,
      0x7e,  0x3,    0x2,    0x2,    0x2,    0x7e,   0x80,   0x3,    0x2,    0x2,   0x2,   0x7f,  0x7d,  0x3,   0x2,
      0x2,   0x2,    0x80,   0x81,   0x7,    0x4,    0x2,    0x2,    0x81,   0x11,  0x3,   0x2,   0x2,   0x2,   0x82,
      0x89,  0x7,    0x23,   0x2,    0x2,    0x83,   0x84,   0x7,    0x6,    0x2,   0x2,   0x84,  0x85,  0x5,   0xe,
      0x8,   0x2,    0x85,   0x86,   0x7,    0x7,    0x2,    0x2,    0x86,   0x88,  0x3,   0x2,   0x2,   0x2,   0x87,
      0x83,  0x3,    0x2,    0x2,    0x2,    0x88,   0x8b,   0x3,    0x2,    0x2,   0x2,   0x89,  0x87,  0x3,   0x2,
      0x2,   0x2,    0x89,   0x8a,   0x3,    0x2,    0x2,    0x2,    0x8a,   0x99,  0x3,   0x2,   0x2,   0x2,   0x8b,
      0x89,  0x3,    0x2,    0x2,    0x2,    0x8c,   0x93,   0x7,    0x23,   0x2,   0x2,   0x8d,  0x8e,  0x7,   0x6,
      0x2,   0x2,    0x8e,   0x8f,   0x5,    0xe,    0x8,    0x2,    0x8f,   0x90,  0x7,   0x7,   0x2,   0x2,   0x90,
      0x92,  0x3,    0x2,    0x2,    0x2,    0x91,   0x8d,   0x3,    0x2,    0x2,   0x2,   0x92,  0x95,  0x3,   0x2,
      0x2,   0x2,    0x93,   0x91,   0x3,    0x2,    0x2,    0x2,    0x93,   0x94,  0x3,   0x2,   0x2,   0x2,   0x94,
      0x96,  0x3,    0x2,    0x2,    0x2,    0x95,   0x93,   0x3,    0x2,    0x2,   0x2,   0x96,  0x97,  0x7,   0x5,
      0x2,   0x2,    0x97,   0x99,   0x5,    0x14,   0xb,    0x2,    0x98,   0x82,  0x3,   0x2,   0x2,   0x2,   0x98,
      0x8c,  0x3,    0x2,    0x2,    0x2,    0x99,   0x13,   0x3,    0x2,    0x2,   0x2,   0x9a,  0xa8,  0x5,   0x24,
      0x13,  0x2,    0x9b,   0xa4,   0x7,    0x8,    0x2,    0x2,    0x9c,   0xa1,  0x5,   0x14,  0xb,   0x2,   0x9d,
      0x9e,  0x7,    0x3,    0x2,    0x2,    0x9e,   0xa0,   0x5,    0x14,   0xb,   0x2,   0x9f,  0x9d,  0x3,   0x2,
      0x2,   0x2,    0xa0,   0xa3,   0x3,    0x2,    0x2,    0x2,    0xa1,   0x9f,  0x3,   0x2,   0x2,   0x2,   0xa1,
      0xa2,  0x3,    0x2,    0x2,    0x2,    0xa2,   0xa5,   0x3,    0x2,    0x2,   0x2,   0xa3,  0xa1,  0x3,   0x2,
      0x2,   0x2,    0xa4,   0x9c,   0x3,    0x2,    0x2,    0x2,    0xa4,   0xa5,  0x3,   0x2,   0x2,   0x2,   0xa5,
      0xa6,  0x3,    0x2,    0x2,    0x2,    0xa6,   0xa8,   0x7,    0x9,    0x2,   0x2,   0xa7,  0x9a,  0x3,   0x2,
      0x2,   0x2,    0xa7,   0x9b,   0x3,    0x2,    0x2,    0x2,    0xa8,   0x15,  0x3,   0x2,   0x2,   0x2,   0xa9,
      0xaa,  0x5,    0x1c,   0xf,    0x2,    0xaa,   0xab,   0x7,    0x23,   0x2,   0x2,   0xab,  0xad,  0x7,   0xa,
      0x2,   0x2,    0xac,   0xae,   0x5,    0x18,   0xd,    0x2,    0xad,   0xac,  0x3,   0x2,   0x2,   0x2,   0xad,
      0xae,  0x3,    0x2,    0x2,    0x2,    0xae,   0xaf,   0x3,    0x2,    0x2,   0x2,   0xaf,  0xb0,  0x7,   0xb,
      0x2,   0x2,    0xb0,   0xb1,   0x5,    0x1e,   0x10,   0x2,    0xb1,   0x17,  0x3,   0x2,   0x2,   0x2,   0xb2,
      0xb7,  0x5,    0x1a,   0xe,    0x2,    0xb3,   0xb4,   0x7,    0x3,    0x2,   0x2,   0xb4,  0xb6,  0x5,   0x1a,
      0xe,   0x2,    0xb5,   0xb3,   0x3,    0x2,    0x2,    0x2,    0xb6,   0xb9,  0x3,   0x2,   0x2,   0x2,   0xb7,
      0xb5,  0x3,    0x2,    0x2,    0x2,    0xb7,   0xb8,   0x3,    0x2,    0x2,   0x2,   0xb8,  0x19,  0x3,   0x2,
      0x2,   0x2,    0xb9,   0xb7,   0x3,    0x2,    0x2,    0x2,    0xba,   0xbb,  0x7,   0x21,  0x2,   0x2,   0xbb,
      0xc7,  0x7,    0x23,   0x2,    0x2,    0xbc,   0xbd,   0x7,    0x6,    0x2,   0x2,   0xbd,  0xc4,  0x7,   0x7,
      0x2,   0x2,    0xbe,   0xbf,   0x7,    0x6,    0x2,    0x2,    0xbf,   0xc0,  0x5,   0x24,  0x13,  0x2,   0xc0,
      0xc1,  0x7,    0x7,    0x2,    0x2,    0xc1,   0xc3,   0x3,    0x2,    0x2,   0x2,   0xc2,  0xbe,  0x3,   0x2,
      0x2,   0x2,    0xc3,   0xc6,   0x3,    0x2,    0x2,    0x2,    0xc4,   0xc2,  0x3,   0x2,   0x2,   0x2,   0xc4,
      0xc5,  0x3,    0x2,    0x2,    0x2,    0xc5,   0xc8,   0x3,    0x2,    0x2,   0x2,   0xc6,  0xc4,  0x3,   0x2,
      0x2,   0x2,    0xc7,   0xbc,   0x3,    0x2,    0x2,    0x2,    0xc7,   0xc8,  0x3,   0x2,   0x2,   0x2,   0xc8,
      0x1b,  0x3,    0x2,    0x2,    0x2,    0xc9,   0xca,   0x9,    0x2,    0x2,   0x2,   0xca,  0x1d,  0x3,   0x2,
      0x2,   0x2,    0xcb,   0xcf,   0x7,    0x8,    0x2,    0x2,    0xcc,   0xce,  0x5,   0x20,  0x11,  0x2,   0xcd,
      0xcc,  0x3,    0x2,    0x2,    0x2,    0xce,   0xd1,   0x3,    0x2,    0x2,   0x2,   0xcf,  0xcd,  0x3,   0x2,
      0x2,   0x2,    0xcf,   0xd0,   0x3,    0x2,    0x2,    0x2,    0xd0,   0xd2,  0x3,   0x2,   0x2,   0x2,   0xd1,
      0xcf,  0x3,    0x2,    0x2,    0x2,    0xd2,   0xd3,   0x7,    0x9,    0x2,   0x2,   0xd3,  0x1f,  0x3,   0x2,
      0x2,   0x2,    0xd4,   0xd7,   0x5,    0x6,    0x4,    0x2,    0xd5,   0xd7,  0x5,   0x22,  0x12,  0x2,   0xd6,
      0xd4,  0x3,    0x2,    0x2,    0x2,    0xd6,   0xd5,   0x3,    0x2,    0x2,   0x2,   0xd7,  0x21,  0x3,   0x2,
      0x2,   0x2,    0xd8,   0xd9,   0x5,    0x28,   0x15,   0x2,    0xd9,   0xda,  0x7,   0x5,   0x2,   0x2,   0xda,
      0xdb,  0x5,    0x24,   0x13,   0x2,    0xdb,   0xdc,   0x7,    0x4,    0x2,   0x2,   0xdc,  0xfb,  0x3,   0x2,
      0x2,   0x2,    0xdd,   0xdf,   0x5,    0x24,   0x13,   0x2,    0xde,   0xdd,  0x3,   0x2,   0x2,   0x2,   0xde,
      0xdf,  0x3,    0x2,    0x2,    0x2,    0xdf,   0xe0,   0x3,    0x2,    0x2,   0x2,   0xe0,  0xfb,  0x7,   0x4,
      0x2,   0x2,    0xe1,   0xfb,   0x5,    0x1e,   0x10,   0x2,    0xe2,   0xe3,  0x7,   0xc,   0x2,   0x2,   0xe3,
      0xe4,  0x7,    0xa,    0x2,    0x2,    0xe4,   0xe5,   0x5,    0x26,   0x14,  0x2,   0xe5,  0xe6,  0x7,   0xb,
      0x2,   0x2,    0xe6,   0xe9,   0x5,    0x22,   0x12,   0x2,    0xe7,   0xe8,  0x7,   0xd,   0x2,   0x2,   0xe8,
      0xea,  0x5,    0x22,   0x12,   0x2,    0xe9,   0xe7,   0x3,    0x2,    0x2,   0x2,   0xe9,  0xea,  0x3,   0x2,
      0x2,   0x2,    0xea,   0xfb,   0x3,    0x2,    0x2,    0x2,    0xeb,   0xec,  0x7,   0xe,   0x2,   0x2,   0xec,
      0xed,  0x7,    0xa,    0x2,    0x2,    0xed,   0xee,   0x5,    0x26,   0x14,  0x2,   0xee,  0xef,  0x7,   0xb,
      0x2,   0x2,    0xef,   0xf0,   0x5,    0x22,   0x12,   0x2,    0xf0,   0xfb,  0x3,   0x2,   0x2,   0x2,   0xf1,
      0xf2,  0x7,    0xf,    0x2,    0x2,    0xf2,   0xfb,   0x7,    0x4,    0x2,   0x2,   0xf3,  0xf4,  0x7,   0x10,
      0x2,   0x2,    0xf4,   0xfb,   0x7,    0x4,    0x2,    0x2,    0xf5,   0xf7,  0x7,   0x11,  0x2,   0x2,   0xf6,
      0xf8,  0x5,    0x24,   0x13,   0x2,    0xf7,   0xf6,   0x3,    0x2,    0x2,   0x2,   0xf7,  0xf8,  0x3,   0x2,
      0x2,   0x2,    0xf8,   0xf9,   0x3,    0x2,    0x2,    0x2,    0xf9,   0xfb,  0x7,   0x4,   0x2,   0x2,   0xfa,
      0xd8,  0x3,    0x2,    0x2,    0x2,    0xfa,   0xde,   0x3,    0x2,    0x2,   0x2,   0xfa,  0xe1,  0x3,   0x2,
      0x2,   0x2,    0xfa,   0xe2,   0x3,    0x2,    0x2,    0x2,    0xfa,   0xeb,  0x3,   0x2,   0x2,   0x2,   0xfa,
      0xf1,  0x3,    0x2,    0x2,    0x2,    0xfa,   0xf3,   0x3,    0x2,    0x2,   0x2,   0xfa,  0xf5,  0x3,   0x2,
      0x2,   0x2,    0xfb,   0x23,   0x3,    0x2,    0x2,    0x2,    0xfc,   0xfd,  0x5,   0x34,  0x1b,  0x2,   0xfd,
      0x25,  0x3,    0x2,    0x2,    0x2,    0xfe,   0xff,   0x5,    0x3c,   0x1f,  0x2,   0xff,  0x27,  0x3,   0x2,
      0x2,   0x2,    0x100,  0x107,  0x7,    0x23,   0x2,    0x2,    0x101,  0x102, 0x7,   0x6,   0x2,   0x2,   0x102,
      0x103, 0x5,    0x24,   0x13,   0x2,    0x103,  0x104,  0x7,    0x7,    0x2,   0x2,   0x104, 0x106, 0x3,   0x2,
      0x2,   0x2,    0x105,  0x101,  0x3,    0x2,    0x2,    0x2,    0x106,  0x109, 0x3,   0x2,   0x2,   0x2,   0x107,
      0x105, 0x3,    0x2,    0x2,    0x2,    0x107,  0x108,  0x3,    0x2,    0x2,   0x2,   0x108, 0x29,  0x3,   0x2,
      0x2,   0x2,    0x109,  0x107,  0x3,    0x2,    0x2,    0x2,    0x10a,  0x10b, 0x7,   0xa,   0x2,   0x2,   0x10b,
      0x10c, 0x5,    0x24,   0x13,   0x2,    0x10c,  0x10d,  0x7,    0xb,    0x2,   0x2,   0x10d, 0x111, 0x3,   0x2,
      0x2,   0x2,    0x10e,  0x111,  0x5,    0x28,   0x15,   0x2,    0x10f,  0x111, 0x5,   0x3e,  0x20,  0x2,   0x110,
      0x10a, 0x3,    0x2,    0x2,    0x2,    0x110,  0x10e,  0x3,    0x2,    0x2,   0x2,   0x110, 0x10f, 0x3,   0x2,
      0x2,   0x2,    0x111,  0x2b,   0x3,    0x2,    0x2,    0x2,    0x112,  0x11d, 0x5,   0x2a,  0x16,  0x2,   0x113,
      0x114, 0x7,    0x23,   0x2,    0x2,    0x114,  0x116,  0x7,    0xa,    0x2,   0x2,   0x115, 0x117, 0x5,   0x30,
      0x19,  0x2,    0x116,  0x115,  0x3,    0x2,    0x2,    0x2,    0x116,  0x117, 0x3,   0x2,   0x2,   0x2,   0x117,
      0x118, 0x3,    0x2,    0x2,    0x2,    0x118,  0x11d,  0x7,    0xb,    0x2,   0x2,   0x119, 0x11a, 0x5,   0x2e,
      0x18,  0x2,    0x11a,  0x11b,  0x5,    0x2c,   0x17,   0x2,    0x11b,  0x11d, 0x3,   0x2,   0x2,   0x2,   0x11c,
      0x112, 0x3,    0x2,    0x2,    0x2,    0x11c,  0x113,  0x3,    0x2,    0x2,   0x2,   0x11c, 0x119, 0x3,   0x2,
      0x2,   0x2,    0x11d,  0x2d,   0x3,    0x2,    0x2,    0x2,    0x11e,  0x11f, 0x9,   0x3,   0x2,   0x2,   0x11f,
      0x2f,  0x3,    0x2,    0x2,    0x2,    0x120,  0x125,  0x5,    0x24,   0x13,  0x2,   0x121, 0x122, 0x7,   0x3,
      0x2,   0x2,    0x122,  0x124,  0x5,    0x24,   0x13,   0x2,    0x123,  0x121, 0x3,   0x2,   0x2,   0x2,   0x124,
      0x127, 0x3,    0x2,    0x2,    0x2,    0x125,  0x123,  0x3,    0x2,    0x2,   0x2,   0x125, 0x126, 0x3,   0x2,
      0x2,   0x2,    0x126,  0x31,   0x3,    0x2,    0x2,    0x2,    0x127,  0x125, 0x3,   0x2,   0x2,   0x2,   0x128,
      0x129, 0x8,    0x1a,   0x1,    0x2,    0x129,  0x12a,  0x5,    0x2c,   0x17,  0x2,   0x12a, 0x130, 0x3,   0x2,
      0x2,   0x2,    0x12b,  0x12c,  0xc,    0x3,    0x2,    0x2,    0x12c,  0x12d, 0x9,   0x4,   0x2,   0x2,   0x12d,
      0x12f, 0x5,    0x2c,   0x17,   0x2,    0x12e,  0x12b,  0x3,    0x2,    0x2,   0x2,   0x12f, 0x132, 0x3,   0x2,
      0x2,   0x2,    0x130,  0x12e,  0x3,    0x2,    0x2,    0x2,    0x130,  0x131, 0x3,   0x2,   0x2,   0x2,   0x131,
      0x33,  0x3,    0x2,    0x2,    0x2,    0x132,  0x130,  0x3,    0x2,    0x2,   0x2,   0x133, 0x134, 0x8,   0x1b,
      0x1,   0x2,    0x134,  0x135,  0x5,    0x32,   0x1a,   0x2,    0x135,  0x13b, 0x3,   0x2,   0x2,   0x2,   0x136,
      0x137, 0xc,    0x3,    0x2,    0x2,    0x137,  0x138,  0x9,    0x5,    0x2,   0x2,   0x138, 0x13a, 0x5,   0x32,
      0x1a,  0x2,    0x139,  0x136,  0x3,    0x2,    0x2,    0x2,    0x13a,  0x13d, 0x3,   0x2,   0x2,   0x2,   0x13b,
      0x139, 0x3,    0x2,    0x2,    0x2,    0x13b,  0x13c,  0x3,    0x2,    0x2,   0x2,   0x13c, 0x35,  0x3,   0x2,
      0x2,   0x2,    0x13d,  0x13b,  0x3,    0x2,    0x2,    0x2,    0x13e,  0x13f, 0x8,   0x1c,  0x1,   0x2,   0x13f,
      0x140, 0x5,    0x34,   0x1b,   0x2,    0x140,  0x146,  0x3,    0x2,    0x2,   0x2,   0x141, 0x142, 0xc,   0x3,
      0x2,   0x2,    0x142,  0x143,  0x9,    0x6,    0x2,    0x2,    0x143,  0x145, 0x5,   0x34,  0x1b,  0x2,   0x144,
      0x141, 0x3,    0x2,    0x2,    0x2,    0x145,  0x148,  0x3,    0x2,    0x2,   0x2,   0x146, 0x144, 0x3,   0x2,
      0x2,   0x2,    0x146,  0x147,  0x3,    0x2,    0x2,    0x2,    0x147,  0x37,  0x3,   0x2,   0x2,   0x2,   0x148,
      0x146, 0x3,    0x2,    0x2,    0x2,    0x149,  0x14a,  0x8,    0x1d,   0x1,   0x2,   0x14a, 0x14b, 0x5,   0x36,
      0x1c,  0x2,    0x14b,  0x151,  0x3,    0x2,    0x2,    0x2,    0x14c,  0x14d, 0xc,   0x3,   0x2,   0x2,   0x14d,
      0x14e, 0x9,    0x7,    0x2,    0x2,    0x14e,  0x150,  0x5,    0x36,   0x1c,  0x2,   0x14f, 0x14c, 0x3,   0x2,
      0x2,   0x2,    0x150,  0x153,  0x3,    0x2,    0x2,    0x2,    0x151,  0x14f, 0x3,   0x2,   0x2,   0x2,   0x151,
      0x152, 0x3,    0x2,    0x2,    0x2,    0x152,  0x39,   0x3,    0x2,    0x2,   0x2,   0x153, 0x151, 0x3,   0x2,
      0x2,   0x2,    0x154,  0x155,  0x8,    0x1e,   0x1,    0x2,    0x155,  0x156, 0x5,   0x38,  0x1d,  0x2,   0x156,
      0x15c, 0x3,    0x2,    0x2,    0x2,    0x157,  0x158,  0xc,    0x3,    0x2,   0x2,   0x158, 0x159, 0x7,   0x16,
      0x2,   0x2,    0x159,  0x15b,  0x5,    0x38,   0x1d,   0x2,    0x15a,  0x157, 0x3,   0x2,   0x2,   0x2,   0x15b,
      0x15e, 0x3,    0x2,    0x2,    0x2,    0x15c,  0x15a,  0x3,    0x2,    0x2,   0x2,   0x15c, 0x15d, 0x3,   0x2,
      0x2,   0x2,    0x15d,  0x3b,   0x3,    0x2,    0x2,    0x2,    0x15e,  0x15c, 0x3,   0x2,   0x2,   0x2,   0x15f,
      0x160, 0x8,    0x1f,   0x1,    0x2,    0x160,  0x161,  0x5,    0x3a,   0x1e,  0x2,   0x161, 0x167, 0x3,   0x2,
      0x2,   0x2,    0x162,  0x163,  0xc,    0x3,    0x2,    0x2,    0x163,  0x164, 0x7,   0x17,  0x2,   0x2,   0x164,
      0x166, 0x5,    0x3a,   0x1e,   0x2,    0x165,  0x162,  0x3,    0x2,    0x2,   0x2,   0x166, 0x169, 0x3,   0x2,
      0x2,   0x2,    0x167,  0x165,  0x3,    0x2,    0x2,    0x2,    0x167,  0x168, 0x3,   0x2,   0x2,   0x2,   0x168,
      0x3d,  0x3,    0x2,    0x2,    0x2,    0x169,  0x167,  0x3,    0x2,    0x2,   0x2,   0x16a, 0x16b, 0x7,   0x24,
      0x2,   0x2,    0x16b,  0x3f,   0x3,    0x2,    0x2,    0x2,    0x26,   0x43,  0x47,  0x4b,  0x54,  0x60,  0x6d,
      0x70,  0x73,   0x7d,   0x89,   0x93,   0x98,   0xa1,   0xa4,   0xa7,   0xad,  0xb7,  0xc4,  0xc7,  0xcf,  0xd6,
      0xde,  0xe9,   0xf7,   0xfa,   0x107,  0x110,  0x116,  0x11c,  0x125,  0x130, 0x13b, 0x146, 0x151, 0x15c, 0x167,
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) {
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

C1Parser::Initializer C1Parser::_init;
