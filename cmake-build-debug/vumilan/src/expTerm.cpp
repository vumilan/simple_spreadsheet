//
// Created by Milan Vu on 2019-05-22.
//

#include "expTerm.h"

/**
 * Constructor of term expression which is just a string/number
 * @param string value
 */
ExpTerm::ExpTerm(std::string value) : stringValue(std::move(value)) {}

/**
 * Constructor of term expression when making a reference to a cell
 * @param cell
 */
ExpTerm::ExpTerm(std::shared_ptr<Cell> cell) : cellPtr(std::move(cell)) {}

/**
 * Constructor of term expression when linked cell makes a cycle
 * @param bool
 */
ExpTerm::ExpTerm(bool cycleDetected) : cycleDetected(cycleDetected) {}

/**
 * Creates parent type pointer to this
 * @return shared_ptr<Exp>
 */
std::shared_ptr<Exp> ExpTerm::clone() const {
    return std::make_shared<ExpTerm>(ExpTerm(*this));
}

/**
 * Evaluate string value of this term expression
 * @return string
 */
std::string ExpTerm::evaluateString() const {
    if (!cycleDetected) {
        if (cellPtr) {
            if (cellPtr->hasError())
                throw ErrorCellLinkException();
            return cellPtr->value();
        }
        return stringValue;
    }
    throw CycleException();
}

/**
 * Evaluate numeric value of this term expression
 * @return double
 */
double ExpTerm::evaluate() const {
    if (cycleDetected)
        throw CycleException();
    std::string tmp = stringValue;
    if (cellPtr) {
        if (cellPtr->hasError())
            throw ErrorCellLinkException();
        tmp = cellPtr->value();
    }
    char *pEnd = nullptr;
    double number = std::strtod(tmp.c_str(), &pEnd);
    if (*pEnd) {
        throw NotANumberException();
    }
    return number;
}
