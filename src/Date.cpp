//
// Created by Milan on 11.05.2019.
//

#include "Date.h"

int Date::getYear() const {
    return year;
}

int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}

std::ostream &Date::print(std::ostream &os) const {
    return os << day << "." << month << "." << year;
}