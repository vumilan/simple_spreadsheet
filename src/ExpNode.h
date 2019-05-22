//
// Created by Milan Vu on 2019-05-22.
//

#ifndef SIMPLE_SPREADSHEET_EXPNODE_H
#define SIMPLE_SPREADSHEET_EXPNODE_H

#include "Exp.h"
#include <iostream>

class ExpNode : public Exp {
public:
    ExpNode(char op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right) : op(op), l_exp(left), r_exp(right) {}

    void print() const {
        std::cout << '(' << op << ' ';
        l_exp->print();
        r_exp->print();
        std::cout << ')';
    }

    std::shared_ptr<Exp> clone() const {
        return std::make_shared<ExpNode>(ExpNode(*this));
    }

private:
    std::shared_ptr<Exp> l_exp;
    std::shared_ptr<Exp> r_exp;
    char op; // +, -, *, /
};


#endif //SIMPLE_SPREADSHEET_EXPNODE_H
