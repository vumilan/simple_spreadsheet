//
// Created by Milan Vu on 2019-05-22.
//

#ifndef SIMPLE_SPREADSHEET_EXPNODE_H
#define SIMPLE_SPREADSHEET_EXPNODE_H

#include "Exp.h"
#include "exceptions/DivisionByZeroException.h"
#include <iostream>
#include <memory>

class ExpNode : public Exp {
public:
    ExpNode(char op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right)
        : op(op), leftExpr(std::move(left)), rightExpr(std::move(right)) {}

    void print() const override {
        std::cout << '(' << op << ' ';
        leftExpr->print();
        rightExpr->print();
        std::cout << ')';
    }

    std::shared_ptr<Exp> clone() const override {
        return std::make_shared<ExpNode>(ExpNode(*this));
    }

    double evaluate() const override {
        if (op == '+')
            return leftExpr->evaluate() + rightExpr->evaluate();
        else if (op == '-')
            return leftExpr->evaluate() - rightExpr->evaluate();
        else if (op == '*')
            return leftExpr->evaluate() * rightExpr->evaluate();
        // op == '/' here
        double rightNumber = rightExpr->evaluate();
        if (rightNumber == 0)
            throw DivisionByZeroException();
        return leftExpr->evaluate() / rightExpr->evaluate();
    }

private:
    std::shared_ptr<Exp> leftExpr;
    std::shared_ptr<Exp> rightExpr;
    char op; // +, -, *, /
};


#endif //SIMPLE_SPREADSHEET_EXPNODE_H
