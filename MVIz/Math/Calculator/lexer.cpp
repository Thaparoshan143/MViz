#include"lexer.h"

Lexer::Lexer(str text) {
    this -> text = text;
    pos = 0;
    current_char = text[pos];
}

void Lexer::Advance() {
    pos += 1;
    
    if (pos > text.length() - 1) {
        current_char = '\0';
    } else {
        current_char = text[pos];
    }
}

void Lexer::SkipWhitespace() {
    if (current_char != '\0' && current_char == ' ') {
        Advance();
    }
}

str Lexer::Integer() {
    str result = "";
    while (current_char != '\0' && isdigit(current_char)) {
        result += current_char;
        Advance();
    }

    return result;
}

Token Lexer::GetNextToken() {
    while (current_char != '\0') {
        if (current_char == ' ') {
            SkipWhitespace();
            continue;
        } 

        if (isdigit(current_char)) { return Token(INTEGER, Integer()); }
        
        switch (current_char) {
            case '+':           Advance();      return Token(PLUS, "+");
            case '-':           Advance();      return Token(MINUS, "-");
            case '*':           Advance();      return Token(MUL, "*");
            case '/':           Advance();      return Token(DIV, "/");
            case '(':           Advance();      return Token(LPAREN, "(");
            case ')':           Advance();      return Token(RPAREN, ")");
            default:            Error();
        }
    }
    return Token(EOT, "None");
}

void Lexer::Error() {
    std::cout << "\nInvalid Character" << std::endl;
    exit(1);
}