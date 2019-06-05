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

    static std::string deleteUselessZeroes(const std::string &str) {
        size_t pos, i;
        if ((pos = str.find('.')) == std::string::npos)
            return str;
        std::string tmp = str.substr(pos);
        for (i = tmp.size() - 1; i >= 0; --i) {
            if (tmp[i] != '0' && tmp[i] != '.')
                break;
        }
        return str.substr(0, pos + i + 1);
    }

    std::string evaluateString() const override {
        return deleteUselessZeroes(std::to_string(this->evaluate()));
    }

private:
    std::shared_ptr<Exp> leftExpr;
    std::shared_ptr<Exp> rightExpr;
    char op; // +, -, *, /
};


#endif //SIMPLE_SPREADSHEET_EXPNODE_H
