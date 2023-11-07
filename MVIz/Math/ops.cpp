#include <vector>
#include <math.h>

// ------------------------------------------------------------------------
// both parameters: list
// ------------------------------------------------------------------------

template <class T, class U>
std::vector<float> add(std::vector<T> a, std::vector<U> b) {
    // error handling: equal length
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] + b[i]);
    }

    return result;
}

template <class T, class U>
std::vector<float> subtract(std::vector<T> a, std::vector<U> b) {
    // error handling: equal length
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] - b[i]);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> multiply(std::vector<T>a, std::vector<U> b) {
    // error handling: equal length
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] * b[i]);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> divide(std::vector<T> a, std::vector<U> b) {
    // error handling: equal length
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] / b[i]);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> pow(std::vector<T> a, std::vector<U> b) {
    // error handlind equal length
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(pow(a[i], b[i]));
    }
    
    return result;
}

// ------------------------------------------------------------------------
// first parameter: constant
// ------------------------------------------------------------------------

template <class T, class U>
std::vector<float> add(T a, std::vector<U> b) {
    std::vector<float> result;

    for (int i = 0; i < b.size(); i++) {
        result.push_back(a + b[i]);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> subtract(T a, std::vector<U> b) {
    std::vector<float> result;

    for (int i = 0; i < b.size(); i++) {
        result.push_back(a - b[i]);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> multiply(T a, std::vector<U> b) {
    std::vector<float> result;

    for (int i = 0; i < b.size(); i++) {
        result.push_back(a * b[i]);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> divide(T a, std::vector<U> b) {
    std::vector<float> result;

    for (int i = 0; i < b.size(); i++) {
        result.push_back(a / b[i]);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> pow(T a, std::vector<U> b) {
    std::vector<float> result;

    for (int i = 0; i < b.size(); i++) {
        result.push_back(pow(a, b[i]));
    }
    
    return result;
}

// ------------------------------------------------------------------------
// second parameter: constant
// ------------------------------------------------------------------------

template <class T, class U>
std::vector<float> add(std::vector<T> a, U b) {
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] + b);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> subtract(std::vector<T> a, U b) {
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] - b);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> multiply(std::vector<T>a, U b) {
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] * b);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> divide(std::vector<T> a, U b) {
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(a[i] / b);
    }
    
    return result;
}

template <class T, class U>
std::vector<float> pow(std::vector<T> a, U b) {
    std::vector<float> result;

    for (int i = 0; i < a.size(); i++) {
        result.push_back(pow(a[i], b));
    }
    
    return result;
}