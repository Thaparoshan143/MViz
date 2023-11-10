#include "interpreter.h"
#include "ast.h"

void Interpreter::Visit(BinOp* exp) {
    exp->children[0]->accept(this);
    double left = result;
    exp->children[1]->accept(this);
    double right = result;

    if (exp->token.GetType() == PLUS) {
        result = left + right;
    } else if (exp->token.GetType() == MINUS) {
        result = left - right;
    } else { throw "Undefined operation!"; }
}

void Interpreter::Visit(Num* num) {
    result = std::atof(num->token.GetValue().c_str());
}