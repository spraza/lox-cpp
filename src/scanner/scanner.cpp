#include "scanner.hpp"
#include "../error_handler/error_handler.hpp"

using namespace lox;

Scanner::Scanner(const std::string& aSource, ErrorHandler& aErrorHandler)
    : start(0)
    , current(0)
    , line(1)
    , source(aSource)
    , errorHandler(aErrorHandler) {}

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
        case '"':
            string();
            break;
        case ' ':
        case '\r':
        case '\t':
            // ignore whitespace
            break;
        case '\n':
            ++line;
            break;
        default: {
            if (isDigit(c)) {
                number();
            } else {
                std::string errorMessage = "Unexpected character: ";
                errorMessage += c;
                errorHandler.add(line, "", errorMessage);
                break;
            }
        }
    }
}

bool Scanner::isDigit(const char c) { return c >= '0' && c <= '9'; }

void Scanner::number() {
    while (isDigit(peek()))
        (void)advanceAndGetChar();
    // look for fractional part
    if (peek() == '.' && isDigit(peekNext())) {
        // consume the "."
        (void)advanceAndGetChar();
        while (isDigit(peek()))
            (void)advanceAndGetChar();
    }
    const size_t numberLength = current - start;
    const std::string numberLiteral = source.substr(start, numberLength);
    addToken(TokenType::NUMBER, numberLiteral);
}

void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n')
            ++line;
        (void)advanceAndGetChar();
    }
    // unterminated string
    if (isAtEnd()) {
        errorHandler.add(line, "", "Unterminated string.");
        return;
    }
    // closing "
    (void)advanceAndGetChar();
    const size_t stringSize = current - start;
    // trim the surrounding quotes
    const std::string stringLiteral = source.substr(start + 1, stringSize - 2);
    addToken(TokenType::STRING, stringLiteral);
}

void Scanner::addToken(const TokenType aTokenType, const std::string& value) {
    const size_t lexemeSize = current - start;
    const auto lexeme = source.substr(start, lexemeSize);
    tokens.push_back(Token(aTokenType, lexeme, value, line));
}

void Scanner::addToken(const TokenType aTokenType) { addToken(aTokenType, ""); }

bool Scanner::isAtEnd() const { return current >= source.size(); }

bool Scanner::matchAndAdvance(const char aExpected) {
    if (isAtEnd())
        return false;
    if (source[current] != aExpected)
        return false;
    ++current;
    return true;
}

char Scanner::peekNext() const {
    if (current + 1 >= source.length())
        return '\0';
    return source[current + 1];
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
    tokens.push_back(Token(TokenType::END_OF_FILE, "", "", line));
    return tokens;
}
