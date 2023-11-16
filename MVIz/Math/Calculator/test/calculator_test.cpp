#include "../calculator.cpp"

int main() {
    std::string text = "(sin(5))^2 + (cos(5))^2 + e + log(e)";
    float result = Calculator(text);
    std::cout << result;
    return 0;
}