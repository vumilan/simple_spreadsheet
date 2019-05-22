//
// Created by Milan on 11.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_DATE_H
#define SIMPLE_SPREADSHEET_DATE_H


#include <ostream>

class Date {
public:
    Date(size_t day, size_t month, size_t year) : year(year), month(month), day(day) {}

    size_t getYear() const;

    size_t getMonth() const;

    size_t getDay() const;

    std::ostream &print(std::ostream &os) const;

private:
    size_t year, month, day;
};


#endif //SIMPLE_SPREADSHEET_DATE_H
