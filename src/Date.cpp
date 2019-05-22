//
// Created by Milan on 11.05.2019.
//

#include "Date.h"

size_t Date::getYear() const {
    return year;
}

size_t Date::getMonth() const {
    return month;
}

size_t Date::getDay() const {
    return day;
}

std::ostream &Date::print(std::ostream &os) const {
    return os << day << "." << month << "." << year;
}