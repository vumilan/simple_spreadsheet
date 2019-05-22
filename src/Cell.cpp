//
// Created by Milan on 11.05.2019.
//

#include "Cell.h"

/**
 * constructor of abstract class Cell
 *
 * @param value
 */
Cell::Cell(const std::string &value) : value(value) {}

/**
 * operator << to call print of child classes
 *
 * @param os
 * @param cell
 * @return
 */
std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    return cell.print(os);
}
