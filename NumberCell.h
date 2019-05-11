//
// Created by Milan on 11.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_NUMBERCELL_H
#define SIMPLE_SPREADSHEET_NUMBERCELL_H

#include "Cell.h"
#include <memory>

class NumberCell : public Cell {
public:
    NumberCell(double number) { m_Number = number; }

    std::shared_ptr<Cell> clone() const override;

//    void convertToSF() const override;
//
//    std::ostream &print(std::ostream &os) const override;

private:
    double m_Number;
};


#endif //SIMPLE_SPREADSHEET_NUMBERCELL_H
