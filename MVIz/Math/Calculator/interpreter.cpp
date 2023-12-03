#include "interpreter.h"
#include "ast.h"
#include <math.h>

#define PI 3.14159265358979323846

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

void Interpreter::Visit(Var* var) {
    result = x_var;
}

void Interpreter::Visit(Function* func) {
    func->children[0]->accept(this);
    double param = result;

    if (func->token.GetValue() == "log") {
        result = log(param);
    } else if (func->token.GetValue() == "sin") {
        result = sin(param);
    } else if (func->token.GetValue() == "cos") {
        result = cos(param);
    } else if (func->token.GetValue() == "tan") {
        result = tan(param);
    } else if (func->token.GetValue() == "cosec") {
        result = 1 / sin(param);
    } else if (func->token.GetValue() == "sec") {
        result = 1 / cos(param);
    } else if (func->token.GetValue() == "cot") {
        result = 1 / tan(param);
    } else if (func->token.GetValue() == "sinh") {
        result = sinh(param);
    } else if (func->token.GetValue() == "cosh") {
        result = cosh(param);
    } else if (func->token.GetValue() == "tanh") {
        result = tanh(param);
    } else if (func->token.GetValue() == "cosech") {
        result = 1 / sinh(param);
    } else if (func->token.GetValue() == "sech") {
        result = 1 / cosh(param);
    } else if (func->token.GetValue() == "coth") {
        result = 1 / tanh(param);
    } else if (func->token.GetValue() == "asin") {
        result = asin(param);
    } else if (func->token.GetValue() == "acos") {
        result = acos(param);
    } else if (func->token.GetValue() == "atan") {
        result = atan(param);
    } else if (func->token.GetValue() == "acosec") {
        result = asin(1 / param);
    } else if (func->token.GetValue() == "asec") {
        result = acos(1 / param);
    } else if (func->token.GetValue() == "acot") {
        result = PI / 2 - atan(param);
    } else if (func->token.GetValue() == "asinh") {
        result = asinh(param);
    } else if (func->token.GetValue() == "acosh") {
        result = acosh(param);
    } else if (func->token.GetValue() == "atanh") {
        result = atanh(param);
    } else if (func->token.GetValue() == "acosech") {
        result = asinh(1 / param);
    } else if (func->token.GetValue() == "asech") {
        result = acosh(1 / param);
    } else if (func->token.GetValue() == "acoth") {
        result = atanh(1 / param);
    }

}