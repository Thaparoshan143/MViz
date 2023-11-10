#pragma once

#include <iostream>

typedef std::string str;

const str INTEGER = "INTEGER";
const str PLUS = "PLUS";
const str MINUS = "MINUS";
const str MUL = "MUL";
const str DIV = "DIV";
const str LPAREN = "(";
const str RPAREN = ")";
const str EOT = "EOT";

class Token {
    public:
        Token(str type, str value) : type(type), value(value) {}
        str GetToken() { return "Token(" + type + ", " + value + ")"; }
        str GetType() { return type; }
        str GetValue() { return value; }
    private:
        str type;
        str value;
};

class Lexer {
    public:
        Lexer(str text);
        void Advance();
        void SkipWhitespace();
        str Integer();
        Token GetNextToken();
        void Error();
    private:
        str text;
        int pos;
        char current_char;
};