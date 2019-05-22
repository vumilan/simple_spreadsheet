//
// Created by Milan on 11.05.2019.
//

#include "NumberCell.h"

NumberCell::NumberCell(const std::string &cellValue, double number) : Cell(cellValue), number(number) {}

std::shared_ptr<Cell> NumberCell::clone() const {
    return std::make_shared<NumberCell>(NumberCell(*this));
}

std::ostream &NumberCell::print(std::ostream &os) const {
    os << std::to_string(number);
    return os;
}

std::string NumberCell::convertToSF() const {
    return "save format of number";
}