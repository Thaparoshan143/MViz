#include "../calculator.cpp"
#include<vector>

int main() {
    std::string text = "-(x^2) + x + 1";
    std::vector<float> result2 = Calculate(text, -10, 10, 0.5);
    return 0;
}