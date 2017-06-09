#include "scanner.hpp"

using namespace lox;

Scanner::Scanner(const std::string& aSource)
    : start(0)
    , current(0)
    , line(1)
    , source(aSource) {}

char Scanner::advanceAndGetChar() {
    ++current;
    return source[current - 1];
}

void Scanner::scanAndAddToken() {
    const char c = advanceAndGetChar();
    switch (c) {
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;
        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;
        case '!':
            addToken(matchAndAdvance('=') ? TokenType::BANG_EQUAL
                                          : TokenType::BANG);
            break;
        case '=':
            addToken(matchAndAdvance('=') ? TokenType::EQUAL_EQUAL
                                          : TokenType::EQUAL);
            break;
        case '<':
            addToken(matchAndAdvance('=') ? TokenType::LESS_EQUAL
                                          : TokenType::LESS);
            break;
        case '>':
            addToken(matchAndAdvance('=') ? TokenType::GREATER_EQUAL
                                          : TokenType::GREATER);
            break;
        case '/':
            if (matchAndAdvance('/')) {
                // a comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd())
                    (void)advanceAndGetChar();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // ignore whitespace
            break;
        case '\n':
            ++line;
            break;
    }
}

void Scanner::addToken(const TokenType aTokenType) {
    const size_t lexemeSize = current - start;
    const auto lexeme = source.substr(start, lexemeSize);
    tokens.push_back(Token(aTokenType, lexeme, line));
}

bool Scanner::isAtEnd() const { return current >= source.size(); }

bool Scanner::matchAndAdvance(const char aExpected) {
    if (isAtEnd())
        return false;
    if (source[current] != aExpected)
        return false;
    ++current;
    return true;
}

char Scanner::peek() const {
    if (isAtEnd())
        return '\0';
    return source[current];
}

std::vector<Token> Scanner::scanAndGetTokens() {
    while (!isAtEnd()) {
        // we are at the beginning of the next lexeme
        start = current;
        scanAndAddToken();
    }

    tokens.push_back(Token(TokenType::END_OF_FILE, "", line));
    return tokens;
}
