#include "visitor.h"

class Interpreter : public Visitor {
    public:
        void Visit(BinOp*);
        void Visit(Num*);

        double Result() { return result; }

    private: 
        double result;
};
