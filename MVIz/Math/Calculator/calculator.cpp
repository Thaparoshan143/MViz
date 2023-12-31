#define LOGGER

#include "interpreter.cpp"
#include "parser.cpp"
#include "lexer.cpp"
#include "../../logger.h"
#include <iostream>
#include <sstream>
#include <vector>


/*
calculates an expression without variables and returns the result.

# Example

```
float result = Calculate(5 * 6 + 6);
```

*/
float Calculate(std::string text) {
    Logger::Log("Initializing Calculator\n", Severity::Info);
    std::string message;
    message = "Calculator Data\n\n\tInput Expression: " + text;
    Lexer lexer(text);
    Parser parser(&lexer);
    auto ast = parser.Expression();

    Interpreter interpreter;
    ast.get()->accept(&interpreter);
    message = message + "\n\tOutput: " + std::to_string(interpreter.Result()) + "\n";
    Logger::Log(message, Severity::Info);
    return interpreter.Result();
}

/*
calculates an expression's right hand side and returns a vector containing the x and 
y values satisfying the expression.

The `step_size` is the distance between each point in the range `x_low` to `x_high`.

setting `normalize = true` returns the vector in a normalized form in the range -1 
to 1.

# Examples

```
std::vector<float> vertices = Calculate("x * cos(x)", -10, 10, 0.015625);
std::vector<float> normalized_vertices = Calculate("x * sin(x)", -10, 10, 0.015625, 5, true);
```

*/
std::vector<float> Calculate(std::string text, float x_low, float x_high, float step_size, int y_high = 1, bool normalize = false){
    Logger::Log("Initializing Calculator\n", Severity::Info);
    std::ostringstream oss;
    if (!normalize) { oss << "Calculator Data\n\n\tInput Expression: " << text; }
    else if (normalize) { oss << "Calculator Data (Normalized)\n\n\tInput Expression: " << text; }
    oss << "\n\n\tVertices:";
    oss << std::setw(6) << "X " << "\t\t\t\tY\n";

    std::string original_text = text;

    std::vector<float> result;

    for (float i = x_low; i <= x_high; i += step_size) {
        oss << "\n\t" << std::setw(15) << i << "\t\t";


        for (int j = 0; j < text.length(); j++) {
            if (text[j] == 'x') {
                text.erase(j, 1);
                text.insert(j, "(" + std::to_string(i) + ")");      // parentheses is to guard the negative x values in expressions like -x^2
            }
        }

        Lexer lexer(text);
        Parser parser(&lexer);
        auto ast = parser.Expression();

        Interpreter interpreter;
        ast.get()->accept(&interpreter);
        oss << std::setw(10) << std::setprecision(3) << interpreter.Result() / y_high << std::setw(10) << interpreter.Result();

        if (normalize) { result.push_back(i / x_high); }
        else if (!normalize) { result.push_back(i); }
        result.push_back(interpreter.Result() / y_high);

        text = original_text;
    }

    oss << "\n";

    Logger::Log(oss.str(), Severity::Info);

    return result;
}