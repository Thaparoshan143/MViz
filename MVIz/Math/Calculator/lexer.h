#pragma once

#include<string.h>
#include <iostream>

#include "token.h"

class Lexer {
    public:
        Lexer(std::string text);
        void Advance();
        void SkipWhitespace();
        std::string Number();
        std::string Trig();
        Token GetNextToken();
        void Error(std::string msg = "");
    private:
        std::string text;
        int pos;
        char current_char;
};

const char* ratios[] = {
    "sin",
    "cos",
    "tan",
    "asin",
    "acos",
    "atan",
    "sinh",
    "cosh",
    "tanh",
    "asinh",
    "acosh",
    "atanh"
};