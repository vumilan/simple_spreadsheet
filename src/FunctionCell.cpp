//
// Created by Milan on 12.05.2019.
//

#include "FunctionCell.h"

std::shared_ptr<Cell> FunctionCell::clone() const {
    return std::make_shared<FunctionCell>(FunctionCell(*this));
}

std::ostream &FunctionCell::print(std::ostream &os) const {
    return os << std::setprecision(9) << value;
}