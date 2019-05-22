//
// Created by Milan on 12.05.2019.
//

#include "FunctionCell.h"

FunctionCell::FunctionCell(const std::string &cellValue, const std::string &function, size_t number)
    : Cell(cellValue), number(number) {}

std::shared_ptr<Cell> FunctionCell::clone() const {
    return std::make_shared<FunctionCell>(FunctionCell(*this));
}

std::ostream &FunctionCell::print(std::ostream &os) const {
    return os << std::setprecision(9) << number;
}

std::string FunctionCell::convertToSF() const {
    return "save format of function";
}