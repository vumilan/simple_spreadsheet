//
// Created by Milan on 12.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_DATECELL_H
#define SIMPLE_SPREADSHEET_DATECELL_H

#include "Date.h"
#include "Cell.h"
#include <memory>

class DateCell : public Cell {
public:
    DateCell(const Date &date) : date(date) {}

    std::shared_ptr<Cell> clone() const override;

//    void convertToSF() const override;
//
    std::ostream &print(std::ostream &os) const override;

private:
    Date date;
};


#endif //SIMPLE_SPREADSHEET_DATECELL_H
