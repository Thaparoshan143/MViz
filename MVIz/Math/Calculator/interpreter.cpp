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
    } else if (func->token.GetValue() == "sinh") {
        result = sinh(param);
    } else if (func->token.GetValue() == "cosh") {
        result = cosh(param);
    } else if (func->token.GetValue() == "tanh") {
        result = tanh(param);
    } else if (func->token.GetValue() == "asin") {
        result = asin(param);
    } else if (func->token.GetValue() == "acos") {
        result = acos(param);
    } else if (func->token.GetValue() == "atan") {
        result = atan(param);
    } else if (func->token.GetValue() == "asinh") {
        result = asinh(param);
    } else if (func->token.GetValue() == "acosh") {
        result = acosh(param);
    } else if (func->token.GetValue() == "atanh") {
        result = atanh(param);
    }

}