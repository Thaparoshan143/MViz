#ifndef AST_H
#define AST_H

#include<memory>
#include "token.h"
#include "visitor.h"
#include<vector>
#include<iostream>


class Node {
    public:
        Node(Token token)
            : token(token) {}

        virtual void accept(Visitor* visitor) = 0;

        virtual ~Node() {}
        void AddChild(std::shared_ptr<Node> child) {
            children.push_back(child);
        }
        
        Token token;
        std::vector<std::shared_ptr<Node>> children;
};

class BinOp : public Node {
    public:
        BinOp(Token token)
            : Node(token) {}

        void accept(Visitor* visitor) {
            return visitor->Visit(this);
        }

        ~BinOp() {}
};

class Num : public Node {
    public:
        Num(Token token)
            : Node(token) {}

        void accept(Visitor* visitor) {
            return visitor->Visit(this);
        }
};

#endif