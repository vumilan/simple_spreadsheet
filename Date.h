//
// Created by Milan on 11.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_DATE_H
#define SIMPLE_SPREADSHEET_DATE_H


class Date {
public:
    Date(int year, int month, int day) : year(year), month(month), day(day) {}

    int getYear() const;

    int getMonth() const;

    int getDay() const;

private:
    int year, month, day;
};


#endif //SIMPLE_SPREADSHEET_DATE_H
