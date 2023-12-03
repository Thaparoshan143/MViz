#include "visitor.h"

class Interpreter : public Visitor {
    public:
        Interpreter(double x = 0) {
            x_var = x;
        }

        void Visit(BinOp*);
        void Visit(Num*);
        void Visit(Function*);
        void Visit(Var*);

        double Result() { return result; }

    private: 
        double result;
        double x_var;
};
