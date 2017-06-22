#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "error_handler/error_handler.hpp"
#include "parser/parser.hpp"
#include "scanner/scanner.hpp"
#include "tools/ast_printer.hpp"

namespace lox {
    static void run(const std::string& source, ErrorHandler& errorHandler) {
        /// scanner
        Scanner scanner(source, errorHandler);
        const auto tokens = scanner.scanAndGetTokens();
        // if found error during scanning, report
        if (errorHandler.foundError) {
            errorHandler.report();
            return;
        }
        /// parser
        Parser parser(tokens, errorHandler);
	auto expr = parser.parse();
	// if found error during parsing, report
        if (errorHandler.foundError) {
            errorHandler.report();
            return;
        }
	/// print ast
	ASTPrinter pp;
	pp.print(expr);
	std::cout << std::endl;
    }

    static void runFile(const std::string& path, ErrorHandler& errorHandler) {
        std::ifstream file(path);
        std::ostringstream stream;
        stream << file.rdbuf();
        file.close();
        run(stream.str(), errorHandler);
    }

    static void runPrompt(ErrorHandler& errorHandler) {
        while (true) {
            std::cout << "> ";
            std::string line;
            getline(std::cin, line);
            run(line, errorHandler);
            if (errorHandler.foundError) {
                errorHandler.clear();
            }
        }
    }
}

int main(int argc, char** argv) {
    lox::ErrorHandler errorHandler;
    if (argc > 2) {
        std::cout << "Usage: lox [filename]" << std::endl;
    } else if (argc == 2) {
        lox::runFile(argv[1], errorHandler);
    } else {
        lox::runPrompt(errorHandler);
    }
    return 0;
}
