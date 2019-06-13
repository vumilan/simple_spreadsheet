//
// Created by Milan Vu on 2019-05-22.
//

#ifndef SIMPLE_SPREADSHEET_EXPTERM_H
#define SIMPLE_SPREADSHEET_EXPTERM_H

#include <string>
#include "exp.h"
#include "cell.h"
#include "exceptions/notANumberException.h"
#include "exceptions/cycleException.h"
#include "exceptions/errorCellLinkException.h"
#include <iostream>


class ExpTerm : public Exp {
public:
    explicit ExpTerm(std::string value);

    explicit ExpTerm(std::shared_ptr<Cell> cell);

    explicit ExpTerm(bool cycleDetected);

    std::shared_ptr<Exp> clone() const override;

    double evaluate() const override;

    std::string evaluateString() const override;

private:
    std::string stringValue;
    std::shared_ptr<Cell> cellPtr = nullptr;
    bool cycleDetected = false;
};


#endif //SIMPLE_SPREADSHEET_EXPTERM_H
