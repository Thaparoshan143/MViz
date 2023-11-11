#include "../parser.cpp"
#include "../lexer.cpp"

int main() {
    std::string text = "2 * 2 + 2";
    Lexer l(text);
    Parser P(&l);

    // std::cout << l.GetNextToken().GetToken() << std::endl;
    // std::cout << l.GetNextToken().GetToken() << std::endl;
    // std::cout << l.GetNextToken().GetToken() << std::endl;

    // std::cout << P.lexer.GetNextToken().GetToken() << std::endl;

    std::cout << P.GetNode() << std::endl;
    return 0;
}