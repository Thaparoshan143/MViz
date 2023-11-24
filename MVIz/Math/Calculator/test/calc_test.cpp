#include "../calculator.cpp"

int main() {
    while (true) {
        std::string text;
        std::cout << "calc> ";
        std::getline(std::cin, text);

        float result = Calculate(text); 
        std::cout << "calc> " << result << std::endl;
    }
    return 0;
}