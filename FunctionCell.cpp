//
// Created by Milan on 12.05.2019.
//

#include "FunctionCell.h"

std::shared_ptr<Cell> FunctionCell::clone() const {
    return std::make_shared<Cell>(FunctionCell(*this));
}