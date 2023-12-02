#pragma once

#include<string.h>
#include <iostream>
#include <math.h>

#include "token.h"

class Lexer {
    public:
        Lexer(std::string text);
        void Advance();
        void SkipWhitespace();
        std::string Number();
        std::string fn();
        Token GetNextToken();
        void Error(std::string msg = "");
    private:
        std::string text;
        int pos;
        char current_char;
};

const char* fn_names[] = {
    "log",
    "sin",
    "cos",
    "tan",
    "cosec",
    "sec",
    "cot",
    "asin",
    "acos",
    "atan",
    "acosec",
    "asec",
    "acot",
    "sinh",
    "cosh",
    "tanh",
    "cosech",
    "sech",
    "coth",
    "asinh",
    "acosh",
    "atanh",
    "acosech",
    "asech",
    "acoth",
};