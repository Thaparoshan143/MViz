#include "../parser.cpp"
#include "../lexer.cpp"

int main() {
    str text = "2 + (2 * 2)";
    Lexer l(text);
    Parser P(l);

    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;

    P.Parse();
    std::cout << P.Parse()->GetNode() << std::endl;
    return 0;
}