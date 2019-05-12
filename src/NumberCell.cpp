//
// Created by Milan on 11.05.2019.
//

#include "NumberCell.h"

std::shared_ptr<Cell> NumberCell::clone() const {
    return std::make_shared<NumberCell>(NumberCell(*this));
}

std::ostream &NumberCell::print(std::ostream &os) const {
    os << std::to_string(number);
    return os;
}