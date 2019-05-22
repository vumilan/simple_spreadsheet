//
// Created by Milan on 12.05.2019.
//

#include "DateCell.h"

/**
 * Constructor
 *
 * @param cellValue
 * @param date
 */
DateCell::DateCell(const std::string &cellValue, const Date &date) : Cell(cellValue), date(date) {}

/**
 * Clones child object, returns a smart pointer of type parent to store in one container
 *
 * @return std::shared_ptr<Cell>
 */
std::shared_ptr<Cell> DateCell::clone() const {
    return std::make_shared<DateCell>(DateCell(*this));
}

/**
 * Prints value of object
 *
 * @param os
 * @return ostream
 */
std::ostream &DateCell::print(std::ostream &os) const {
    return date.print(os);
}

/**
 * Converts cell into save format
 *
 * @return string
 */
std::string DateCell::convertToSF() const {
    return "save format of cell";
}