//
// Created by Milan Vu on 2019-05-29.
//

#ifndef SIMPLE_SPREADSHEET_NOTANUMBEREXCEPTION_H
#define SIMPLE_SPREADSHEET_NOTANUMBEREXCEPTION_H

/// Thrown when math operators are used for strings
class NotANumberException : public std::exception {
public:
    /// Implicit constructor
    NotANumberException() = default;
    /// Implicit destructor
    ~NotANumberException() override = default;
};

#endif //SIMPLE_SPREADSHEET_NOTANUMBEREXCEPTION_H
