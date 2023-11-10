#include "../lexer.cpp"

int main() {
    std::string text = "2 * 2 + (3 * 4)";

    Lexer l(text);
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    
    return 0;
}