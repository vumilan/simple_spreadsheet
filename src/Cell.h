//
// Created by Milan on 11.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_CELL_H
#define SIMPLE_SPREADSHEET_CELL_H

#include <memory>
#include <iostream>

/// virtual class Cell
class Cell {
public:

    Cell() = default;

    virtual std::shared_ptr<Cell> clone() const = 0;

    virtual ~Cell() = default;

//    /// polymorphic virtual function
//    /// converts value of cell into save format
//    /// const = 0 means each child class inheriting from parent class Cell has to have it's own implementation of this function
//    virtual void convertToSF() const = 0;
//
//    /// function to load cell value from save format
//    void loadFromSF();
//
    virtual std::ostream &print(std::ostream &os) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Cell &cell);

};

#endif //SIMPLE_SPREADSHEET_CELL_H
