#include <vector>
#include <iostream>

void base_log(std::vector<float> vec) {
    std::cout << "[";
    int index = 0;
    for (const auto element : vec) {
        std::cout << element;
        if (index == vec.size() - 1) { continue; }
        std::cout << " ";
        index++;
    }
    std::cout << "]";
}

void log(std::vector<float> vec) {
    std::cout << std::endl;
    base_log(vec);
}

void log(std::vector<std::vector<float>> vec) {
    std::cout << std::endl;
    std::cout << "[";
    int index = 0;
    for(const auto row : vec) {
        base_log(row);
        if (index == vec.size() - 1) { continue; }
        std::cout << std::endl << " ";
        index++;
    }
    std::cout << "]";
    std::cout << std::endl;
}