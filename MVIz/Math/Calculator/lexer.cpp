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

std::string Lexer::Number() {
    std::string result = "";
    int decimal_count = 0;
    while ((current_char != '\0' && isdigit(current_char))
            || current_char == '.') {
        if (current_char == '.') { decimal_count += 1; }

        if (decimal_count > 1) { Error("More than one decimals."); }

        result += current_char;
        Advance();
    }

    return result;
}

std::string Lexer::fn() {
    std::string result = "";
    while (current_char >= 97 && current_char <= 122) {
        result += current_char;
        Advance();
    }

    for (int i = 0; i < 13; i++) {
        if (result == fn_names[i]){
            return result;
        }
    }

    Error(result);
    return "";
}

Token Lexer::GetNextToken() {
    int decimal_count = 0;
    char last_char;
    while (current_char != '\0') {
        if (current_char == ' ') {
            SkipWhitespace();
            continue;
        } 


        if (isdigit(current_char)) { 
            last_char = current_char;
            return Token(TokenType::NUM, Number()); 
        }
        decimal_count = 0;

        if (current_char == 'e') { 
            Advance();
            return Token(TokenType::NUM, std::to_string(exp(1))); 
        }

        if (current_char >= 97 && current_char <= 122) {
            return Token(TokenType::FUNCTION, fn());
        }
        
        switch (current_char) {
            case '+':
                Advance();      
                return Token(TokenType::PLUS, "+");
            case '-':  
                Advance();      
                return Token(TokenType::MINUS, "-");
            case '*':      
                Advance();      
                return Token(TokenType::MUL, "*");
            case '/':
                Advance();      
                return Token(TokenType::DIV, "/");
            case '^':          
                Advance();      
                return Token(TokenType::POW, "^");
            case '(':           
                Advance();      
                return Token(TokenType::LPAREN, "(");
            case ')':           
                Advance();      
                return Token(TokenType::RPAREN, ")");
            default:            Error();
        }
    }
    return Token(TokenType::EOF_TYPE, "None");
}

void Lexer::Error(std::string msg) {
    try 
    {
        std::cout << "\nInvalid Character! " + msg;
    }
    catch(std::string err)
    {
        throw std::string("Invalid Character! ");
    }
}