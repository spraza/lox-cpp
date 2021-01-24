#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <string>
#include <vector>

namespace lox {
    class ErrorHandler {
      public:
        struct ErrorInfo {
            int line;
            std::string where;
            std::string message;
        };
        ErrorHandler();
        void report() const;
        void add(int line, const std::string& where,
                 const std::string& message);
        void clear();
        bool foundError;

      private:
        std::vector<ErrorInfo> errorList;
    };
} // namespace lox

#endif // ERROR_HANDLER_HPP
