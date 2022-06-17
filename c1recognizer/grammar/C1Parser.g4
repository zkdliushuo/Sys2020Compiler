parser grammar C1Parser;
options { tokenVocab = C1Lexer; }

compilationUnit: start+;
start: decl | funcdef;
decl: constdecl | vardecl;
constdecl: Const Int constdef(Comma constdef)*SemiColon;
constdef: Identifier (LeftBracket constexp RightBracket)* Assign constinitval; 
// constdef: Identifier (LeftBracket exp RightBracket)* Assign constinitval;
constinitval: constexp 
        |  LeftBrace (constinitval (Comma constinitval)*)? RightBrace;
constexp: addexp;
vardecl: Int vardef(Comma vardef)*SemiColon;
vardef: Identifier (LeftBracket constexp RightBracket)*
        | Identifier (LeftBracket constexp RightBracket)* Assign initval;
initval: exp | LeftBrace (initval (Comma initval)*)? RightBrace;
funcdef: functype Identifier LeftParen funcfparams? RightParen block;
funcfparams: funcfparam (Comma funcfparam)* ; 
funcfparam: Int Identifier (LeftBracket RightBracket (LeftBracket exp RightBracket)*)?; 
functype: Void | Int;
block: LeftBrace blockbody* RightBrace;
blockbody: decl | stmt;
stmt:   lval Assign exp SemiColon 
        | (exp)? SemiColon
        | block 
        | If LeftParen cond RightParen stmt (Else stmt)?
        | While LeftParen cond RightParen stmt
        | Break SemiColon
        | Continue SemiColon
        | Return (exp)? SemiColon;
exp: addexp;
cond: lorexp;
lval:   Identifier (LeftBracket exp RightBracket)*;
primaryexp: LeftParen exp RightParen
        | lval
        | number;
unaryexp: primaryexp
        | Identifier LeftParen (funcrparams)? RightParen
        | unaryop unaryexp;
unaryop: Plus | Minus | Negative;
funcrparams: exp (Comma exp)*;
mulexp: unaryexp 
        | mulexp (Multiply | Divide | Modulo) unaryexp;
addexp: mulexp 
        | addexp (Plus | Minus) mulexp;
relexp: addexp 
        | relexp (Less | Greater | LessEqual | GreaterEqual) addexp;
eqexp: relexp 
        | eqexp (Equal | NonEqual) relexp;
landexp: eqexp 
        | landexp LogicalAnd eqexp;
lorexp: landexp
        | lorexp LogicalOr landexp;
number: IntConst;
