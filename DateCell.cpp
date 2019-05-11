//
// Created by Milan on 12.05.2019.
//

#include "DateCell.h"

std::shared_ptr<Cell> DateCell::clone() const {
    return std::make_shared<Cell>(DateCell(*this));
}