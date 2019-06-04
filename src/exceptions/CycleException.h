//
// Created by Milan Vu on 2019-06-04.
//

#ifndef SIMPLE_SPREADSHEET_CYCLEEXCEPTION_H
#define SIMPLE_SPREADSHEET_CYCLEEXCEPTION_H

class CycleException : public std::exception {
public:
    /// Implicit constructor
    CycleException() = default;
    /// Implicit destructor
    ~CycleException() override = default;
};

#endif //SIMPLE_SPREADSHEET_CYCLEEXCEPTION_H
