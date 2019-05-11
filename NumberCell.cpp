//
// Created by Milan on 11.05.2019.
//

#include "NumberCell.h"

std::shared_ptr<Cell> NumberCell::clone() const {
    return std::make_shared<Cell>(NumberCell(*this));
}
