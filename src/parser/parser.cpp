#include "parser.hpp"
#include <vector>

using namespace lox;

ParseError::ParseError(std::string msg, Token token)
    : std::runtime_error(msg)
    , token_(token) {}

Parser::Parser(const std::vector<Token>& tokens)
    : current(0)
    , tokens_(tokens) {}

Expr* Parser::expression() {
    return equality();
}

Expr* Parser::equality() {
    Expr* expr = comparison();
    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        Token Operator = previous();
        Expr* right    = comparison();
        expr           = new BinaryExpr(expr, Operator, right);
    }
    return expr;
}

Expr* Parser::comparison() {
    Expr* expr = term();
    while (
        match({TokenType::GREATER, TokenType::LESS, TokenType::LESS_EQUAL})) {
        Token Operator = previous();
        Expr* right    = term();
        expr           = new BinaryExpr(expr, Operator, right);
    }
    return expr;
}

Expr* Parser::term() {
    Expr* expr = factor();
    while (match({TokenType::MINUS, TokenType::PLUS})) {
        Token Operator = previous();
        Expr* right    = factor();
        expr           = new BinaryExpr(expr, Operator, right);
    }
    return expr;
}

Expr* Parser::factor() {
    Expr* expr = unary();
    while (match({TokenType::SLASH, TokenType::STAR})) {
        Token Operator = previous();
        Expr* right    = unary();
        expr           = new BinaryExpr(expr, Operator, right);
    }
    return expr;
}

Expr* Parser::unary() {
    if (match({TokenType::BANG, TokenType::MINUS})) {
        Token Operator = previous();
        Expr* right    = unary();
        return new UnaryExpr(Operator, right);
    }
    return primary();
}

Expr* Parser::primary() {
    if (match({TokenType::FALSE}))
        return new LiteralExpr("false");
    if (match({TokenType::TRUE}))
        return new LiteralExpr("true");
    if (match({TokenType::NIL}))
        return new LiteralExpr("nil");
    if (match({TokenType::NUMBER, TokenType::STRING}))
        return new LiteralExpr(previous().literal);
    if (match({TokenType::LEFT_PAREN})) {
        Expr* expr = expression();
        consume(TokenType::RIGHT_PAREN, "Exppect ')' after expression.");
        return new GroupingExpr(expr);
    }
    throw error(peek(), "Expect expression.");
    return nullptr;
}

Expr* Parser::parse() {
    try {
        return expression();
    } catch (ParseError error) {
        return nullptr;
    }
}
Token Parser::consume(TokenType type, std::string message) {
    if (check(type))
        return advance();
    throw error(peek(), message);
}

ParseError Parser::error(Token token, std::string message) {
    if (token.type == TokenType::END_OF_FILE) {
    } else {
    }
    return *new ParseError(message, token);
}

bool Parser::match(const std::vector<TokenType>& types) {
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::previous() {
    return tokens_[current - 1];
}

Token Parser::advance() {
    if (!isAtEnd())
        ++current;
    return previous();
}

Token Parser::peek() {
    return tokens_[current];
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

bool Parser::check(TokenType type) {
    if (isAtEnd())
        return false;
    return peek().type == type;
}
