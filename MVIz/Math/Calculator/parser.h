#pragma once

#include "lexer.h"
#include "ast.h"

class Parser {
    public:
        Parser(Lexer* lexer) : 
            lexer(lexer),
            current_token(lexer->GetNextToken()) {}

        std::shared_ptr<Node> Expression();
        std::shared_ptr<Node> Number();
        std::shared_ptr<Node> Term();
        std::shared_ptr<Node> Power();
        void Consume(TokenType tokenType);

        std::string GetNode() { return Expression().get()->token.GetValue(); }
        
    private:
        Lexer* lexer;
        Token current_token;
};