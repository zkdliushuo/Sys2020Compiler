
// Generated from /home/chivier/compiler/c1recognizer/grammar/C1Lexer.g4 by ANTLR 4.7.2

#pragma once

#include <bits/stdc++.h>

#include <antlr4-runtime.h>

class C1Lexer : public antlr4::Lexer {
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

  C1Lexer(antlr4::CharStream *input);
  ~C1Lexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string> &getRuleNames() const override;

  virtual const std::vector<std::string> &getChannelNames() const override;
  virtual const std::vector<std::string> &getModeNames() const override;
  virtual const std::vector<std::string> &getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary &getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN &getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};
