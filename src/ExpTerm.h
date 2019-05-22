//
// Created by Milan Vu on 2019-05-22.
//

#ifndef SIMPLE_SPREADSHEET_EXPTERM_H
#define SIMPLE_SPREADSHEET_EXPTERM_H

#include <string>
#include "Exp.h"


class ExpTerm : public Exp {
public:
    ExpTerm(const std::string &v): val(v){}

    void print() const {
        std::cout << ' ' << val << ' ';
    }

    std::shared_ptr<Exp> clone() const {
        return std::make_shared<ExpTerm>(ExpTerm(*this));
    }

private:
    std::string val;
};


#endif //SIMPLE_SPREADSHEET_EXPTERM_H
