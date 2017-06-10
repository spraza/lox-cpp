#include "token.hpp"

using namespace lox;

Token::Token(const TokenType aType, const std::string& aLexeme,
             const std::string& aLiteral, const int aLine)
    : type(aType)
    , lexeme(aLexeme)
    , literal(aLiteral)
    , line(aLine) {}

std::string Token::toString() const {
    // for literals, use actual value
    if (type == TokenType::IDENTIFIER || type == TokenType::STRING ||
        type == TokenType::NUMBER) {
        return literal;
    }

    return lexeme;
}
