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

    float last_result;

    Logger::Log("Started Computation of Vertices...\n", Severity::Info);
    std::cout << "here in calculator" << std::endl;
    Lexer lexer(text);
    Parser parser(&lexer);
    auto ast = parser.Expression();

    for (float i = x_low; i <= x_high; i += step_size) {
        oss << "\n\t" << std::setw(15) << i << "\t\t";
        
            Interpreter interpreter(i);
            ast.get()->accept(&interpreter);

            if (normalize) { result.push_back(i / x_high); }
            else if (!normalize) { result.push_back(i); }

            if (last_result > y_high && interpreter.Result() < -y_high) {   // add nan to break -infinity to infinity line
                result.push_back(std::numeric_limits<float>::quiet_NaN());
                oss << std::setw(10) << std::numeric_limits<float>::quiet_NaN();

                if (normalize) { result.push_back(i / x_high); }
                else if (!normalize) { result.push_back(i); }

                result.push_back(-y_high);
            } else if (last_result < -y_high && interpreter.Result() > y_high) {    // add nan to break infinity to -infinity line
                result.push_back(std::numeric_limits<float>::quiet_NaN());
                oss << std::setw(10) << std::numeric_limits<float>::quiet_NaN();

                if (normalize) { result.push_back(i / x_high); }
                else if (!normalize) { result.push_back(i); }

                result.push_back(y_high);
            } else {
                result.push_back(interpreter.Result() / y_high);
                oss << std::setw(10) << std::setprecision(3) << interpreter.Result() / y_high << std::setw(10) << interpreter.Result();
            }

            text = original_text;

            last_result = interpreter.Result();
        
    }
    Logger::Log("Finished Computation of Vertices\n", Severity::Info);
    oss << "\n";

    Logger::SetFilepath("calclog.txt");
    Logger::Log(oss.str(), Severity::Info, std::ios::trunc);
    Logger::RestoreDefaultFilepath();

    return result;
}