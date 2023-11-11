#include "../interpreter.cpp"
#include "../parser.cpp"
#include "../lexer.cpp"
#include <iostream>

int main() {
    while(true) {
        std::string text;
        std::cout << "calc> ";
        getline(std::cin, text);
        Lexer lexer(text);
        Parser parser(&lexer);
        auto ast = parser.Expression();

        Interpreter interpreter;
        ast.get()->accept(&interpreter);
        std::cout << "calc> " << interpreter.Result() << std::endl;
    }
    return 0;
}