#include "parser.h"

void Parser::Consume(TokenType type) {
    if (current_token.GetType() == type) {
        current_token = lexer->GetNextToken();
    } else { 
        std::cout << "Invalid Syntax: Unexpected Token!\nExpected " +
                      ToString(current_token.GetType()) +
                      " got " + ToString(type);
        exit(1);
     }
}

std::shared_ptr<Node> Parser::Number() {
    auto token = current_token;

    // Create a node of type Num
    if (token.GetType() == TokenType::NUM) {
        Consume(TokenType::NUM);
        return std::make_shared<Num>(token);
    } else if (token.GetType() == TokenType::LPAREN) {
        Consume(TokenType::LPAREN);
        auto root = Expression();
        Consume(TokenType::RPAREN);
        return root;
    } else if (token.GetType() == TokenType::FUNCTION) {
        Consume(TokenType::FUNCTION);
        Consume(TokenType::LPAREN);
        auto param = Expression();
        auto root  = std::make_shared<Function>(token);
        root->AddChild(param);
        Consume(TokenType::RPAREN);
        return root;
    } else if (token.GetType() == TokenType::PLUS) {
        // for cases like (+4).

        Consume(TokenType::PLUS);
        
        auto root = Expression();
        return root;
    } else if (token.GetType() == TokenType::MINUS) {
        // for cases like (-4).

        Consume(TokenType::MINUS);
        auto root = std::make_shared<BinOp>(token);
        auto l_token = Token(TokenType::NUM, "0");
        auto left = std::make_shared<Num>(l_token);

        auto right = Expression();
        root -> AddChild(left);
        root -> AddChild(right);
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