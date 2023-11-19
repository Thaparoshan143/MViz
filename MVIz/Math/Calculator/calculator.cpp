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

std::vector<float> Calculate(std::string text, float low, float high, float step_size = 1) {
    Logger::Log("Initializing Calculator\n", Severity::Info);
    std::ostringstream oss;
    oss << "Calculator Data\n\n\tInput Expression: " << text;
    oss << "\n\n\tVertices:";
    oss << std::setw(6) << "X " << "\t\t\t\tY\n";

    std::string original_text = text;

    std::vector<float> result;


    for (float i = low; i <=  high; i += step_size) {
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
        oss << std::setw(10) << std::setprecision(3) << interpreter.Result();

        result.push_back(interpreter.Result());

        text = original_text;
    }

    oss << "\n";

    Logger::Log(oss.str(), Severity::Info);

    return result;
}