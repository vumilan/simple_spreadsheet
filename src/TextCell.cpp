//
// Created by Milan on 12.05.2019.
//

#include "TextCell.h"

std::shared_ptr<Cell> TextCell::clone() const {
    return std::make_shared<TextCell>(TextCell(*this));
}

std::ostream &TextCell::print(std::ostream &os) const {
    os << text;
    return os;
}