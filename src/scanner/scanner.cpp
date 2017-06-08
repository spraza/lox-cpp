#include "scanner.hpp"

using namespace lox;

Token::Token(const TokenType aType, const std::string& aLexeme, const int aLine)
    : type(aType)
    , lexeme(aLexeme)
    , line(aLine) {}

std::string Token::toString() const { return /*type + " " + */ lexeme; }

Scanner::Scanner(const std::string& aSource)
    : start(0)
    , current(0)
    , line(1)
    , source(aSource) {}

void Scanner::processToken() {}

void Scanner::addToken() {}

bool Scanner::isAtEnd() { return current >= source.size(); }

std::vector<Token> Scanner::scanAndGetTokens() {
    while (!isAtEnd()) {
        // we are at the beginning of the next lexeme
        start = current;
        processToken();
    }

    tokens.push_back(Token(TokenType::END_OF_FILE, "eof", line));
    return tokens;
}
