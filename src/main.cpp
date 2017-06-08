#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "scanner/scanner.hpp"

namespace lox {
    static void run(const std::string& source) {
        Scanner scanner(source);
        const auto tokens = scanner.scanAndGetTokens();
        for (const auto token : tokens) {
            std::cout << token.toString() << std::endl;
        }
    }

    static void runFile(const std::string& path) {
        std::ifstream file(path);
        std::ostringstream stream;
        stream << file.rdbuf();
        file.close();
        run(stream.str());
    }

    static void runPrompt() {
        while (true) {
            std::cout << "> ";
            std::string line;
            getline(std::cin, line);
            run(line);
        }
    }
}

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cout << "Usage: lox [filename]" << std::endl;
    } else if (argc == 2) {
        lox::runFile(argv[1]);
    } else {
        lox::runPrompt();
    }
    return 0;
}
