//
// Created by Milan Vu on 2019-05-22.
//

#ifndef SIMPLE_SPREADSHEET_EXPNODE_H
#define SIMPLE_SPREADSHEET_EXPNODE_H

#include "exp.h"
#include "exceptions/divisionByZeroException.h"
#include <iostream>
#include <memory>
#include <sstream>

/// Expression which is a node, holds two expressions and an operator between them
class ExpNode : public Exp {
public:
    ExpNode(char op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right);

    std::shared_ptr<Exp> clone() const override;

    double evaluate() const override;

    std::string evaluateString() const override;

private:
    char op; // +, -, *, /
    std::shared_ptr<Exp> leftExpr;
    std::shared_ptr<Exp> rightExpr;
};


#endif //SIMPLE_SPREADSHEET_EXPNODE_H
