//
// Created by Milan on 12.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_TEXTCELL_H
#define SIMPLE_SPREADSHEET_TEXTCELL_H

#include "string"
#include "Cell.h"
#include <memory>


class TextCell : public Cell {
public:
    TextCell(const std::string &value) { text = value; }

    std::shared_ptr<Cell> clone() const override;

//    void convertToSF() const override;
//
    std::ostream &print(std::ostream &os) const override;

protected:
    std::string text;
};

#endif //SIMPLE_SPREADSHEET_TEXTCELL_H
