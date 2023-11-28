#include "ops.cpp"
#include "log.cpp"
#include "trigonometric.cpp"

int main() {
    std::vector<float> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 3, 4, 5};

    float a_c = 2;
    int b_c = 4;
    
    // std::vector<float> y_1 = sin(a);

    // additions

    std::vector<float> add_1 = add(
        multiply(sin(a), sin(a)), 
        multiply(cos(b), cos(b))
    );
    std::vector<float> add_2 = add(a_c, b);
    std::vector<float> add_3 = add(a, b_c);

    std::cout << "\n\nAdditions: ";
    log(add_1);
    log(add_2);
    log(add_3);

    // subtractions

    std::vector<float> sub_1 = subtract(
        multiply(cosh(a), cosh(a)),
        multiply(sinh(a), sinh(a))
    );
    std::vector<float> sub_2 = subtract(a_c, b);
    std::vector<float> sub_3 = subtract(a, b_c);

    std::cout << "\n\n Subtractions: ";
    log(sub_1);
    log(sub_2);
    log(sub_3);

    // multiplications

    std::vector<float> mul_1 = multiply(a, b);
    std::vector<float> mul_2 = multiply(a_c, b);
    std::vector<float> mul_3 = multiply(a, b_c);

    std::cout << "\n\nMultiplications: ";
    log(mul_1);
    log(mul_2);
    log(mul_3);

    // divisions

    std::vector<float> div_1 = divide(a, b);
    std::vector<float> div_2 = divide(a_c, b);
    std::vector<float> div_3 = divide(a, b_c);

    std::cout << "\n\nDivisions: ";
    log(div_1);
    log(div_2);
    log(div_3);

    // power

    std::vector<float> pow_1 = pow(a, b);
    std::vector<float> pow_2 = pow(a_c, b);
    std::vector<float> pow_3 = pow(a, b_c);

    std::cout << "\n\nPowers: ";
    log(pow_1);
    log(pow_2);
    log(pow_3);

    // template tests: addition
    std::vector<int> a_int = {1, 2, 3, 4, 5};
    std::vector<int> b_int = {1, 2, 3, 4, 5};
    std::vector<float> add_int = add(a_int, b_int);

    std::cout << "\n\nInt list additions: ";
    log(add_int);
}