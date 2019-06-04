//
// Created by Milan Vu on 2019-05-29.
//

#ifndef SIMPLE_SPREADSHEET_DEVISIONBYZEROEXCEPTION_H
#define SIMPLE_SPREADSHEET_DEVISIONBYZEROEXCEPTION_H

class DivisionByZeroException : public std::exception {
public:
    /// Implicit constructor
    DivisionByZeroException() = default;
    /// Implicit destructor
    ~DivisionByZeroException() override = default;
};

#endif //SIMPLE_SPREADSHEET_DEVISIONBYZEROEXCEPTION_H
