#include "token.hpp"

using namespace lox;

Token::Token(const TokenType aType, const std::string& aLexeme, const int aLine)
    : type(aType)
    , lexeme(aLexeme)
    , line(aLine) {}

std::string Token::toString() const { return /*type + " " + */ lexeme; }
