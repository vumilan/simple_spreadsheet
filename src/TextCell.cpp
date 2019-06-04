//
// Created by Milan on 12.05.2019.
//

#include "TextCell.h"

TextCell::TextCell(std::string formula, std::string value)
    : Cell(std::move(formula)), stringValue(std::move(value)) {}

std::shared_ptr<Cell> TextCell::clone() const {
    return std::make_shared<TextCell>(TextCell(*this));
}

std::ostream &TextCell::print(std::ostream &os) const {
    os << stringValue;
    return os;
}

std::string TextCell::convertToSF() const {
    return "save format of text";
}
