#include "interpreter.cpp"
#include "parser.cpp"
#include "lexer.cpp"
#include "../../logger.h"
#include <iostream>
#include <sstream>
#include <vector>

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

// Returns x and y co-ordinates
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
                text.insert(j, std::to_string(i));
            }
        }

        Lexer lexer(text);
        Parser parser(&lexer);
        auto ast = parser.Expression();

        Interpreter interpreter;
        ast.get()->accept(&interpreter);
        oss << std::setw(10) << std::setprecision(3) << interpreter.Result() / y_high;

        if (normalize) { result.push_back(i / x_high); }
        else if (!normalize) { result.push_back(i); }
        result.push_back(interpreter.Result() / y_high);

        text = original_text;
    }

    oss << "\n";

    Logger::Log(oss.str(), Severity::Info);

    return result;
}