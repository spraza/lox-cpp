#include <string>
#include <vector>

namespace lox {
    class Token {
      public:
        Token(const std::string& aLexeme) : lexeme(aLexeme) {}
        std::string lexeme;
    };

    class Scanner {
      public:
        Scanner(const std::string& aSource) : source(aSource) {}
        std::vector<Token> scanAndGetTokens();

      private:
        std::string source;
        std::vector<Token> tokens;
    };
}
