#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

namespace lox {
    enum class TokenType {
        // Single-character tokens.
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        COMMA,
        DOT,
        MINUS,
        PLUS,
        SEMICOLON,
        SLASH,
        STAR,

        // One or two character tokens.
        BANG,
        BANG_EQUAL,
        EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,

        // Literals.
        IDENTIFIER, // user-defined (e.g. variable/type name) or
                    // language-defined (reserved keyword)
        STRING,
        NUMBER,

        // Reserved Keywords.
        // Reserved keywords ARE identifiers but have seperate token types
        AND,
        CLASS,
        ELSE,
        FALSE,
        FUN,
        FOR,
        IF,
        NIL,
        OR,
        PRINT,
        RETURN,
        SUPER,
        THIS,
        TRUE,
        VAR,
        WHILE,

        END_OF_FILE
    };

    class Token {
      public:
        Token(TokenType aType, const std::string& aLexeme,
              const std::string& aLiteral, int aLine);
        std::string toString() const;

      private:
        TokenType type;
        std::string lexeme;
        // @brief literal can be of 3 types: string, number, or identifier
        // number literals are tricky and it may seem odd that i'm storing them
        // in a string here, but having a "polymorphic" type for literal is more
        // work which is why i'm using a string for now and will convert to
        // number if needed.
        std::string literal;
        int line;
    };
}

#endif // TOKEN_HPP
