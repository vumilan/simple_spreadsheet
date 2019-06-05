//
// Created by Milan Vu on 2019-05-22.
//

#include "ExpTerm.h"

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
