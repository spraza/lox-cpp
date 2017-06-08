#include <string>
#include <vector>

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
        IDENTIFIER,
        STRING,
        NUMBER,

        // Keywords.
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
        Token(TokenType aType, const std::string& aLexeme, int aLine);
        std::string toString() const;

      private:
        TokenType type;
        std::string lexeme;
        int line;
    };

    class Scanner {
      public:
        Scanner(const std::string& aSource);
        std::vector<Token> scanAndGetTokens();

      private:
        ///@brief scans and adds tokens
        void processToken();
        /// @brief adds token to tokens list
        void addToken();
        /// @brief scans the entire source and calls processToken on each
        bool isAtEnd();
        /// @brief index in source string to first character in current lexeme
        size_t start;
        /// @brief index in source string to the current lexeme
        size_t current;
        /// @brief line number of current lexeme
        size_t line;
        /// @brief string containing the entire lox source code
        std::string source;
        /// @brief list of all tokens
        std::vector<Token> tokens;
    };
}
