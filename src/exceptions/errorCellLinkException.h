//
// Created by Milan Vu on 2019-06-04.
//

#ifndef SIMPLE_SPREADSHEET_ERRORCELLLINKEXCEPTION_H
#define SIMPLE_SPREADSHEET_ERRORCELLLINKEXCEPTION_H

/// Thrown when a cell with an error is being referenced
class ErrorCellLinkException : public std::exception {
public:
    /// Implicit constructor
    ErrorCellLinkException() = default;
    /// Implicit destructor
    ~ErrorCellLinkException() override = default;
};

#endif //SIMPLE_SPREADSHEET_ERRORCELLLINKEXCEPTION_H
