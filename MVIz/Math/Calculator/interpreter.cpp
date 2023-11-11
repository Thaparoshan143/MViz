#include "interpreter.h"
#include "ast.h"
#include <math.h>

void Interpreter::Visit(BinOp* exp) {
    exp->children[0]->accept(this);
    double left = result;
    exp->children[1]->accept(this);
    double right = result;

    if (exp->token.GetType() == PLUS) {
        result = left + right;
    } else if (exp->token.GetType() == MINUS) {
        result = left - right;
    } else if (exp->token.GetType() == MUL) {
        result = left * right;
    } else if (exp->token.GetType() == DIV) {
        result = left / right;
    } else {
        printf("Undefined Operation!");
        exit(1);
    }
}

void Interpreter::Visit(Num* num) {
    result = std::atof(num->token.GetValue().c_str());
}

void Interpreter::Visit(TrigRatio* trig) {
    trig->children[0]->accept(this);
    double angle = result;

    if (trig->token.GetValue() == "sin") {
        result = sin(angle);
    } else if (trig->token.GetValue() == "cos") {
        result = cos(angle);
    } else if (trig->token.GetValue() == "tan") {
        result = tan(angle);
    } 
}