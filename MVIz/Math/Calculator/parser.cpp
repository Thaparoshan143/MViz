#include "parser.h"

void Parser::Consume(TokenType type) {
    if (current_token.GetType() == type) {
        current_token = lexer->GetNextToken();
    } else { 
        std::cout << "Invalid Syntax: Unexpected Token!";
        exit(1);
     }
}

std::shared_ptr<Node> Parser::Number() {
    auto token = current_token;

    if (token.GetType() == TokenType::INTEGER) {
        Consume(TokenType::INTEGER);
        return std::make_shared<Num>(token);
    } else { 
        std::cout << "Invalid Syntax: Undefined Token!";
        exit(1);
    }

    return nullptr;

}

std::shared_ptr<Node> Parser::Expression() {
    auto root = Number();

    while (current_token.GetType() == TokenType::PLUS || current_token.GetType() == TokenType::MINUS) {
        auto token = current_token;

        if (token.GetType() == TokenType::PLUS) {
            Consume(PLUS);
        } else if (token.GetType() == TokenType::MINUS) {
            Consume(MINUS);
        }


        auto left = root;
        auto right = Number();
        root = std::make_shared<BinOp>(token);
        root->AddChild(left);
        root->AddChild(right);
    }

    if (current_token.GetType() == TokenType::EOF_TYPE) {
        printf("Accepted!\n");
    } else { 
        std::cout << "Invalid Syntax: Unexpected Token!"; 
        exit(1);
    }

    return root;
}