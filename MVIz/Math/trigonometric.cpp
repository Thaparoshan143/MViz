#include <math.h>
#include <iostream>
#include <vector>
// #include "./log.cpp"

std::vector<float> sin(float x_low, float x_high, int points) {
    std::vector<float> y;
    float it_length = (x_high - x_low) / (points - 1);
    float current_it_length = x_low;
    for (int i = 0; i < points; i+= 1) {
        y.push_back(sin(current_it_length));
        current_it_length += it_length;
    }
    return y;
}

// ------------------------------------------------
// trigonometric functions: parameter is list.
// ------------------------------------------------

template <class T>
std::vector<float> sin(std::vector<T> x) {
    std::vector<float> result;

    for (int i = 0; i < x.size(); i++) {
        result.push_back(sin(x[i]));
    }

    return result;
}

template <class T>
std::vector<float> cos(std::vector<T> x) {
    std::vector<float> result;

    for (int i = 0; i < x.size(); i++) {
        result.push_back(cos(x[i]));
    }

    return result;
}

template <class T>
std::vector<float> tan(std::vector<T> x) {
    std::vector<float> result;

    for (int i = 0; i < x.size(); i++) {
        result.push_back(tan(x[i]));
    }

    return result;
}

// -----------------------------------------------------
// hyperbolic trigonometric functions: parameter is list
// -----------------------------------------------------

template <class T>
std::vector<float> sinh(std::vector<T> x) {
    std::vector<float> result;

    for (int i = 0; i < x.size(); i++) {
        result.push_back(sinh(x[i]));
    }

    return result;
}

template <class T>
std::vector<float> cosh(std::vector<T> x) {
    std::vector<float> result;

    for (int i = 0; i < x.size(); i++) {
        result.push_back(cosh(x[i]));
    }

    return result;
}

template <class T>
std::vector<float> tanh(std::vector<T> x) {
    std::vector<float> result;

    for (int i = 0; i < x.size(); i++) {
        result.push_back(tanh(x[i]));
    }

    return result;
}