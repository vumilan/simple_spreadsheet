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

    explicit Cell(std::string formula);

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

    virtual const std::string &value() const {
        return formulaValue;
    }

    virtual void setExpTree(std::shared_ptr<Exp> &expTree) {
    }

    virtual bool hasError() const {
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

    const std::string &formula() const {
        return formulaValue;
    }

    void replaceFromRelations(std::shared_ptr<Cell> &thisPtr, std::shared_ptr<Cell> &newPtr);

    bool updateCellRelations(std::shared_ptr<Cell> &ancestorCell, std::shared_ptr<Cell> &thisCell);

    const std::set<std::shared_ptr<Cell>> &getDescendantCells() const;

    void setDescendantCells(const std::set<std::shared_ptr<Cell>> &newDescendantCells);

    const std::set<std::shared_ptr<Cell>> &getAncestorCells() const;

    void setAncestorCells(const std::set<std::shared_ptr<Cell>> &newAncestorCells);

protected:
    std::string formulaValue;
    /// descendantCells is a set of pointers to cells that are referenced by this cell
    std::set<std::shared_ptr<Cell>> descendantCells;
    /// ancestorCells is a set of pointers to cells that referenced this cell
    std::set<std::shared_ptr<Cell>> ancestorCells;
};

#endif //SIMPLE_SPREADSHEET_CELL_H
