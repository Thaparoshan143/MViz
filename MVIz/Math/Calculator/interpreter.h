#include "visitor.h"

class Interpreter : public Visitor {
    public:
        void Visit(BinOp*);
        void Visit(Num*);
        void Visit(TrigRatio*);

        double Result() { return result; }

    private: 
        double result;
};
