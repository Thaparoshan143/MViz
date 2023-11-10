#pragma once

#include "lexer.h"

class AST {
    public:
        virtual ~AST() {}
        virtual str GetNode() = 0;

};

class Node : public AST {
    public:
        Node(AST* left, Token op, AST* right) : 
            left(left), 
            op(op), 
            right(right) {}
        str GetNode() override { 
            return "(" + left->GetNode() + ", " + op.GetValue() + ", " + right->GetNode() + ")"; 
        }
    private:
        AST* left;
        Token op;
        AST* right;
};

class Num : public AST {
    public:
        Num(Token token) : 
            token(token), 
            value(token.GetValue()) {}
        str GetNode() override { return value; }
    private:
        Token token;
        str value;
};

class Parser {
    public:
        Parser(Lexer lexer) : 
            lexer(lexer),
            current_token(lexer.GetNextToken()) {}
        void Consume(str tokenType);
        AST* Factor();
        AST* Term();
        AST* Expr();
        AST* Parse();
        void Error();
    private:
        Lexer lexer;
        Token current_token;
};