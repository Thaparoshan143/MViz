#include "interpreter.h"
#include "parser.h"
#include "lexer.h"
#include <iostream>

float Calculator(std::string text) {
    Lexer lexer(text);
    Parser parser(&lexer);
    auto ast = parser.Expression();

    Interpreter interpreter;
    ast.get()->accept(&interpreter);
    return interpreter.Result();
}