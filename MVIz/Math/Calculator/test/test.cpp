#include "../lexer.cpp"

int main() {
    std::string text = "sin(30)";

    Lexer l(text);
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
    std::cout << l.GetNextToken().GetToken() << std::endl;
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