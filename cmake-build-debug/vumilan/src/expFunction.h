//
// Created by Milan Vu on 2019-06-04.
//

#ifndef SIMPLE_SPREADSHEET_EXPFUNCTION_H
#define SIMPLE_SPREADSHEET_EXPFUNCTION_H

#include "exp.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include "exceptions/errorCellLinkException.h"

/// Expression which is a function class
class ExpFunction : public Exp {
public:
    ExpFunction(int functionType, std::shared_ptr<Exp> &expTree);

    ExpFunction(int functionType, std::vector<std::shared_ptr<Exp>> &expTrees);

    std::shared_ptr<Exp> clone() const override;

    double evaluate() const override;

    std::string evaluateString() const override;

private:
    int functionType;
    std::vector<std::shared_ptr<Exp>> expTrees;
};


#endif //SIMPLE_SPREADSHEET_EXPFUNCTION_H
