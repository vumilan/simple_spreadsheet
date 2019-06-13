//
// Created by Milan on 12.05.2019.
//

#include "textCell.h"

/**
 * Constructor of text cell
 * @param formula
 */
TextCell::TextCell(std::string formula, std::string value)
        : Cell(std::move(formula)), stringValue(std::move(value)) {}

/**
* Creates parent type pointer to this
* @return shared_ptr<Cell>
*/
std::shared_ptr<Cell> TextCell::clone() const {
    return std::make_shared<TextCell>(TextCell(*this));
}

/**
 * Prints formula and cell value into ostream
 * @param os
 * @return ostream
 */
std::ostream &TextCell::print(std::ostream &os) const {
    os << stringValue;
    return os;
}

/**
 * Getter of the value of this cell
 * @return string
 */
const std::string &TextCell::value() const {
    return stringValue;
}