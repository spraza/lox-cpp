#ifndef PARSER_HPP
#define PARSER_HPP

#include "../Expr.hpp"
#include "../scanner/token.hpp"
#include <vector>

namespace lox {
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
