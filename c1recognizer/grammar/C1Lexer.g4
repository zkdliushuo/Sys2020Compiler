lexer grammar C1Lexer;

tokens {
    Comma,
    SemiColon,
    Assign,
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,
    LeftParen,
    RightParen,
    If,
    Else,
    While,
    Break,
    Continue,
    Return,
    Const,
    Equal,
    NonEqual,
    Negative,
    LogicalAnd,
    LogicalOr,
    Less,
    Greater,
    LessEqual,
    GreaterEqual,
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulo,

    Int,
    Void,

    Identifier,
    IntConst
}

Comma: ',';
SemiColon: ';';
Assign: '=';
LeftBracket: '[';
RightBracket: ']';
LeftBrace: '{';
RightBrace: '}';
LeftParen: '(';
RightParen: ')';
If: 'if';
Else: 'else';
While: 'while';
Break: 'break';
Continue: 'continue';
Return: 'return';
Const: 'const';
Equal: '==';
NonEqual: '!=';
Negative: '!';
LogicalAnd: '&&';
LogicalOr: '||';
Less: '<';
Greater: '>';
LessEqual: '<=';
GreaterEqual: '>=';
Plus: '+';
Minus: '-';
Multiply: '*';
Divide: '/';
Modulo: '%';

Int: 'int';
Void: 'void';

Identifier: [a-zA-Z_] [0-9a-zA-Z_]*;

IntConst: '0' [0-7]*
        | [1-9] [0-9]*
        | '0' [xX] [0-9a-fA-F]+;

LineComment: ('//' | '/\\' ('\r'? '\n') '/') ~[\r\n\\]* ('\\' ('\r'? '\n')? ~[\r\n\\]*)* '\r'? '\n' -> skip;
BlockComment: '/*' .*? '*/' -> skip;

WhiteSpace: [ \t\r\n]+ -> skip;
