//
// Created by Milan on 12.05.2019.
//

#include "DateCell.h"

std::shared_ptr<Cell> DateCell::clone() const {
    return std::make_shared<DateCell>(DateCell(*this));
}

std::ostream &DateCell::print(std::ostream &os) const {
    return date.print(os);
}