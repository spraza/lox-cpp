#ifndef PARSER_HPP
#define PARSER_HPP

#include "../Expr.hpp"
#include "../scanner/token.hpp"
#include <stdexcept>
#include <vector>

namespace lox {
    class ParseError : public std::runtime_error {
      public:
        ParseError(std::string msg, Token token);
      Token token_;
    };

    class Parser {
      public:
        Parser(const std::vector<Token>& tokens);
        size_t current;
        Expr* expression();
        Expr* equality();
        Expr* comparison();
        Expr* term();
        Expr* factor();
        Expr* unary();
        Expr* primary();
      Expr* parse();
        ParseError error(Token token, std::string message);

      private:
        bool match(const std::vector<TokenType>& types);
        Token previous();
        Token advance();
        Token peek();
        bool isAtEnd();
        bool check(TokenType type);
        Token consume(TokenType type, std::string message);
        std::vector<Token> tokens_;
    };
}

#endif // PARSER_HPP
