#include"lexer.h"

Lexer::Lexer(std::string text) {
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

std::string Lexer::Integer() {
    std::string result = "";
    while (current_char != '\0' && isdigit(current_char)) {
        result += current_char;
        Advance();
    }

    return result;
}

std::string Lexer::Trig() {
    std::string result = "";
    while (current_char >= 97 && current_char <= 122) {
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

        if (isdigit(current_char)) { return Token(TokenType::INTEGER, Integer()); }

        if (current_char >= 97 && current_char <= 122) {
            return Token(TokenType::TRIG, Trig());
        }
        
        switch (current_char) {
            case '+':           Advance();      return Token(TokenType::PLUS, "+");
            case '-':           Advance();      return Token(TokenType::MINUS, "-");
            case '*':           Advance();      return Token(TokenType::MUL, "*");
            case '/':           Advance();      return Token(TokenType::DIV, "/");
            case '(':           Advance();      return Token(TokenType::LPAREN, "(");
            case ')':           Advance();      return Token(TokenType::RPAREN, ")");
            default:            Error();
        }
    }
    return Token(TokenType::EOF_TYPE, "None");
}

void Lexer::Error() {
    std::cout << "\nInvalid Character" << std::endl;
    exit(1);
}