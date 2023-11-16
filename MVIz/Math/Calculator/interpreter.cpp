#include "interpreter.h"
#include "ast.h"
#include <math.h>

void Interpreter::Visit(BinOp* exp) {
    exp->children[0]->accept(this);
    double left = result;
    exp->children[1]->accept(this);
    double right = result;

    if (exp->token.GetType() == TokenType::PLUS) {
        result = left + right;
    } else if (exp->token.GetType() == TokenType::MINUS) {
        result = left - right;
    } else if (exp->token.GetType() == TokenType::MUL) {
        result = left * right;
    } else if (exp->token.GetType() == TokenType::DIV) {
        result = left / right;
    } else if (exp->token.GetType() == TokenType::POW) {
        result = pow(left, right);
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
    } else if (trig->token.GetValue() == "sinh") {
        result = sinh(angle);
    } else if (trig->token.GetValue() == "cosh") {
        result = cosh(angle);
    } else if (trig->token.GetValue() == "tanh") {
        result = tanh(angle);
    } else if (trig->token.GetValue() == "asin") {
        result = asin(angle);
    } else if (trig->token.GetValue() == "acos") {
        result = acos(angle);
    } else if (trig->token.GetValue() == "atan") {
        result = atan(angle);
    } else if (trig->token.GetValue() == "asinh") {
        result = asinh(angle);
    } else if (trig->token.GetValue() == "acosh") {
        result = acosh(angle);
    } else if (trig->token.GetValue() == "atanh") {
        result = atanh(angle);
    }

}