//
// Created by Milan on 11.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_CELL_H
#define SIMPLE_SPREADSHEET_CELL_H

#include <memory>
#include <iostream>
#include <set>
#include <string>
#include "Exp.h"

/// Parent virtual class Cell for various types of cells
class Cell {
public:

    Cell(const std::string &value);

    virtual ~Cell() = default;

    /// polymorphic function that converts cell into save format
    virtual std::string convertToSF() const = 0;

    /**
     * polymorphic function to access child classes
     *
     * @return pointer to child class which is the type of parent class
     */
    virtual std::shared_ptr<Cell> clone() const = 0;

    virtual std::ostream &print(std::ostream &os) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);
protected:
    std::string value;
    /// cellsTo is a set of pointers to refresh value of the cells referencing from this cell
    std::set<std::shared_ptr<Cell>> cellsTo;
    /// cellsFrom is a set of pointers to get values of the cells referenced by this cell
    std::set<std::shared_ptr<Cell>> cellsFrom;

    std::shared_ptr<Exp> expressionTree;
};

#endif //SIMPLE_SPREADSHEET_CELL_H
