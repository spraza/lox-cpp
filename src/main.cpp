#include <iostream>
#include <string>

namespace lox {
    static void runFile(const std::string& path) {
        std::cout << "TODO: run " << path << std::endl;
    }

    static void run(const std::string& source) {
        std::cout << "TODO: run " << source << std::endl;
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
