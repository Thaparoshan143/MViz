#ifndef VISITOR_H
#define VISITOR_H

class BinOp;
class Num;

class Visitor {
    public:
        virtual void Visit(BinOp*) = 0;
        virtual void Visit(Num*) = 0;
};

#endif