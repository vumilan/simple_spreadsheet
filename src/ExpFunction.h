//
// Created by Milan Vu on 2019-06-04.
//

#ifndef SIMPLE_SPREADSHEET_EXPFUNCTION_H
#define SIMPLE_SPREADSHEET_EXPFUNCTION_H

#include "Exp.h"
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include "exceptions/ErrorCellLinkException.h"

class ExpFunction : public Exp {
public:
    ExpFunction(int functionType, std::shared_ptr<Exp> &expTree) : functionType(functionType) {
        expTrees.push_back(expTree);
    }

    ExpFunction(int functionType, std::vector<std::shared_ptr<Exp>> &expTrees)
        : functionType(functionType), expTrees(expTrees) {
    }

    std::shared_ptr<Exp> clone() const override {
        return std::make_shared<ExpFunction>(ExpFunction(*this));
    }

    double evaluate() const override {
        return std::stod(this->evaluateString());
    }

    std::string evaluateString() const override {
        std::string strOut;
        if (functionType == 4) {
            for (const auto &expTree : expTrees) {
                strOut += expTree->evaluateString();
            }
            return strOut;
        } else {
            strOut = expTrees[0]->evaluateString();
            if (functionType == 1) {
                return std::to_string(sin(std::stod(strOut)));
            } else if (functionType == 2) {
                return std::to_string(cos(std::stod(strOut)));
            } else {
                return std::to_string(abs(std::stod(strOut)));
            }
        }
    }

private:
    int functionType;
    std::vector<std::shared_ptr<Exp>> expTrees;
};


#endif //SIMPLE_SPREADSHEET_EXPFUNCTION_H
