#include "error_handler.hpp"
#include <iostream>

using namespace lox;

ErrorHandler::ErrorHandler()
    : errorList()
    , foundError(false) {}

void ErrorHandler::report() const {
    for (const auto error : errorList) {
        std::cout << "[line " + std::to_string(error.line) + "] Error" +
                         error.where + ": " + error.message
                  << std::endl;
    }
}

void ErrorHandler::add(int line, const std::string& where,
                       const std::string& message) {
    errorList.push_back({line, where, message});
    foundError = true;
}

void ErrorHandler::clear() {
    errorList.clear();
}
