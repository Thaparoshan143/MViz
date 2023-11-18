#include "interpreter.cpp"
#include "parser.cpp"
#include "lexer.cpp"
#include "../../logger.h"
#include <iostream>

float Calculator(std::string text) {
    Logger::Log("Initializing Calculator\n", Severity::Info);
    std::string message;
    message = "Calculator Data\n\n\tInput Expression: " + text;
    Lexer lexer(text);
    Parser parser(&lexer);
    auto ast = parser.Expression();

    Interpreter interpreter;
    ast.get()->accept(&interpreter);
    message = message + "\n\tOutput: " + std::to_string(interpreter.Result()) + "\n";
    Logger::Log(message, Severity::Info);
    return interpreter.Result();
}