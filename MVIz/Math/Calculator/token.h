#pragma once
#include<string>

enum TokenType {
    INTEGER,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LPAREN,
    RPAREN,
    EOF_TYPE
};

const char* TokenNames[] = {
    "INTEGER",
    "PLUS",
    "MINUS",
    "MUL",
    "DIV",
    "LPAREN",
    "RPAREN",
    "EOF"
};

class Token {
    public:
        Token(TokenType type, std::string value) : type(type), value(value) {}
        std::string GetToken() { return "Token(" + ToString(type) + ", " + value + ")"; }
        TokenType GetType() { return type; }
        std::string GetValue() { return value; }
        std::string ToString(TokenType type) {
            return TokenNames[type];
        }
    private:
        TokenType type;
        std::string value;
};

