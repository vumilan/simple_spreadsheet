//
// Created by Milan Vu on 2019-06-01.
//

#include "FormulaCell.h"

FormulaCell::FormulaCell(std::string formula) : Cell(std::move(formula)) {}

std::shared_ptr<Cell> FormulaCell::clone() const {
    return std::make_shared<FormulaCell>(FormulaCell(*this));
}

std::ostream &FormulaCell::print(std::ostream &os) const {
    os << stringValue;
    return os;
}

std::string FormulaCell::convertToSF() const {
    return "save format of formula";
}
