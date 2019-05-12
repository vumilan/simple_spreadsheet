//
// Created by Milan on 11.05.2019.
//

#include "Cell.h"

std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    return cell.print(os);
}
