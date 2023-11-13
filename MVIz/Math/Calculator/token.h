#pragma once
#include<string>

enum TokenType {
    NUM,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    TRIG,
    EOF_TYPE
};

const char* TokenNames[] = {
    "NUM",
    "PLUS",
    "MINUS",
    "MUL",
    "DIV",
    "LPAREN",
    "RPAREN",
    "TRIG",
    "EOF"
};

std::string ToString(TokenType type) {
    return TokenNames[type];
}

class Token {
    public:
        Token(TokenType type, std::string value) : type(type), value(value) {}
        std::string GetToken() { return "Token(" + ToString(type) + ", " + value + ")"; }
        TokenType GetType() { return type; }
        std::string GetValue() { return value; }
    private:
        TokenType type;
        std::string value;
};

