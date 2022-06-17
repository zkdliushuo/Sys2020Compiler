#include <iostream>

#include "antlr4-runtime.h"
#include "C1Lexer.h"

using namespace antlr4;

int main(int argc, const char* argv[]) {
    //std::ifstream infile(argv[1]);
    ANTLRInputStream input(std::cin);
    C1Lexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << std::endl;
    }

    return 0;
}