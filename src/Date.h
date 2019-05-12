//
// Created by Milan on 11.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_DATE_H
#define SIMPLE_SPREADSHEET_DATE_H


#include <ostream>

class Date {
public:
    Date(int day, int month, int year) : year(year), month(month), day(day) {}

    int getYear() const;

    int getMonth() const;

    int getDay() const;

    std::ostream &print(std::ostream &os) const;

private:
    int year, month, day;
};


#endif //SIMPLE_SPREADSHEET_DATE_H
