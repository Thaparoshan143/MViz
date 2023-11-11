#pragma once

#include<string.h>
#include <iostream>

#include "token.h"

class Lexer {
    public:
        Lexer(std::string text);
        void Advance();
        void SkipWhitespace();
        std::string Integer();
        std::string Trig();
        Token GetNextToken();
        void Error();
    private:
        std::string text;
        int pos;
        char current_char;
};