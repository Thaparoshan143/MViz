#include "../calculator.cpp"
#include<vector>

int main() {
    std::string text = "2 + 2";
    float result = Calculator(text);
    std::cout << result;
    return 0;
}