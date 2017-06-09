#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <vector>

#include "token.hpp"

namespace lox {
    class Scanner {
      public:
        Scanner(const std::string& aSource);
        std::vector<Token> scanAndGetTokens();

      private:
        /// @brief advance and get current char
        char advanceAndGetChar();
        ///@brief scans and adds tokens
        void scanAndAddToken();
        /// @brief adds token to tokens list
        void addToken(TokenType);
        /// @brief scans the entire source and calls processToken on each
        bool isAtEnd() const;
        /// @brief Returns true iff the given char matches the current char.
        ///        Also advances current if there is a match.
        bool matchAndAdvance(char);
        /// @brief Like advance but doesn't consume character - basically
        /// "looksahead"
        char peek() const;
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

#endif //SCANNER_HPP
