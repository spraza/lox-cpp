#include "scanner.hpp"

using namespace lox;

std::vector<Token> Scanner::scanAndGetTokens() {
    std::vector<Token> tokens;
    tokens.push_back(Token("dummytoken1"));
    tokens.push_back(Token("dummytoken2"));
    tokens.push_back(Token("dummytoken3"));
    return tokens;
}
