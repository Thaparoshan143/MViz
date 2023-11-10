#include "../interpreter.cpp"
#include "../parser.cpp"
#include "../lexer.cpp"
#include <iostream>

int main() {
    std::string text = "3 + 2 -9";
    Lexer lexer(text);
    Parser parser(&lexer);
    auto ast = parser.Expression();

    Interpreter interpreter;
    ast.get()->accept(&interpreter);
    std::cout << "result: " << interpreter.Result() << std::endl;
    return 0;
}