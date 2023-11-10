#include "parser.h"

void Parser::Consume(str tokenType) {
    if (current_token.GetType() == tokenType) {
        current_token = lexer.GetNextToken();
    } else { Error(); }
}

AST* Parser::Factor() {
    Token token = current_token;
    if (current_token.GetType() == INTEGER) {
        Consume(INTEGER);
        return new Num(token);
    } else if (current_token.GetType() == LPAREN) {
        Consume(LPAREN);
        AST* node = Expr();
        Consume(RPAREN);
        return node;
    }
    return nullptr;
}

AST* Parser::Term() {
    AST* node = Factor();

    while (current_token.GetType() == MUL || current_token.GetType() == DIV) {
        Token token = current_token;
        if (token.GetType() == MUL) { 
            Consume(MUL); 
        } else if (token.GetType() == DIV) {
            Consume(DIV);
        }

        node = new Node(node, token, Factor());
    }

    return node;
}

AST* Parser::Expr() {
    AST* node = Term();

    while (current_token.GetType() == PLUS || current_token.GetType() == MINUS) {
        Token token = current_token;
        if (token.GetType() == PLUS) {
            Consume(PLUS);
        } else if (token.GetType() == MINUS) {
            Consume(MINUS);
        }
        
        node = new Node(node, token, Term());
    }
    return node;
}

AST* Parser::Parse() {
    return Expr();
}

void Parser::Error() {
    std::cout << "Invalid Syntax" << std::endl;
    exit(1);
}