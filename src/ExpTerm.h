//
// Created by Milan Vu on 2019-05-22.
//

#ifndef SIMPLE_SPREADSHEET_EXPTERM_H
#define SIMPLE_SPREADSHEET_EXPTERM_H

#include <string>
#include "Exp.h"
#include "Cell.h"
#include "exceptions/NotANumberException.h"
#include "exceptions/CycleException.h"
#include "exceptions/ErrorCellLinkException.h"
#include <iostream>


class ExpTerm : public Exp {
public:
    explicit ExpTerm(std::string value): stringValue(std::move(value)) {}

    explicit ExpTerm(std::shared_ptr<Cell> cell): cellPtr(std::move(cell)) {}

    explicit ExpTerm(bool cycleDetected) : cycleDetected(cycleDetected) {}

    std::shared_ptr<Exp> clone() const override {
        return std::make_shared<ExpTerm>(ExpTerm(*this));
    }

    double evaluate() const override;

    std::string evaluateString() const override {
        if (!cycleDetected) {
            if (cellPtr) {
                if (cellPtr->hasError())
                    throw ErrorCellLinkException();
                return cellPtr->value();

            }
            return stringValue;
        }
        throw ErrorCellLinkException();
    }

private:
    std::string stringValue;
    std::shared_ptr<Cell> cellPtr = nullptr;
    bool cycleDetected = false;
};


#endif //SIMPLE_SPREADSHEET_EXPTERM_H
