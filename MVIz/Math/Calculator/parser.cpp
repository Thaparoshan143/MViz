#include "parser.h"

void Parser::Consume(TokenType type) {
    if (current_token.GetType() == type) {
        current_token = lexer->GetNextToken();
    } else { 
        std::cout << "Invalid Syntax: Unexpected Token!\nExpected " +
                      ToString(current_token.GetType()) +
                      "Got " + ToString(type);
        exit(1);
     }
}

std::shared_ptr<Node> Parser::Number() {
    auto token = current_token;

    if (token.GetType() == TokenType::NUM) {
        Consume(TokenType::NUM);
        return std::make_shared<Num>(token);
    } else if (token.GetType() == TokenType::LPAREN) {
        Consume(TokenType::LPAREN);
        auto root = Expression();
        Consume(TokenType::RPAREN);
        return root;
    } else if (token.GetType() == TokenType::TRIG) {
        Consume(TokenType::TRIG);
        Consume(TokenType::LPAREN);
        auto angle = Expression();
        auto root  = std::make_shared<TrigRatio>(token);
        root->AddChild(angle);
        Consume(TokenType::RPAREN);
        return root;
    }
    else {
        printf("Invalid Syntax: Unexpected Token!");
        exit(1);
    }
}

std::shared_ptr<Node> Parser::Term() {
    auto root = Number();

    while (current_token.GetType() == TokenType::MUL
            || current_token.GetType() == TokenType::DIV
            || current_token.GetType() == TokenType::LPAREN
            || current_token.GetType() == TokenType::POW) {
        auto token = current_token;

        if (token.GetType() == TokenType::POW) {
            Consume(TokenType::POW);
        } else if (token.GetType() == TokenType::MUL) {
            Consume(TokenType::MUL);
        } else if (token.GetType() == TokenType::DIV) {
            Consume(TokenType::DIV);
        } else if (token.GetType() == TokenType::LPAREN) {
            token = Token(TokenType::MUL, "*");
        }

        auto left = root;
        auto right = Number();
        root = std::make_shared<BinOp>(token);
        root->AddChild(left);
        root->AddChild(right);
    }
    
    return root;
}

std::shared_ptr<Node> Parser::Expression() {
    auto root = Term();

    while (current_token.GetType() == TokenType::PLUS || current_token.GetType() == TokenType::MINUS) {
        auto token = current_token;

        if (token.GetType() == TokenType::PLUS) {
            Consume(TokenType::PLUS);
        } else if (token.GetType() == TokenType::MINUS) {
            Consume(TokenType::MINUS);
        }


        auto left = root;
        auto right = Term();
        root = std::make_shared<BinOp>(token);
        root->AddChild(left);
        root->AddChild(right);
    }

    return root;
}