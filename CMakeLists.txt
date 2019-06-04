cmake_minimum_required(VERSION 2.8.4)
project(simple_spreadsheet)

set(CMAKE_CXX_STANDARD 14)

add_executable(simple_spreadsheet main.cpp src/Cell.cpp src/Cell.h src/Date.cpp src/Date.h src/TextCell.cpp src/TextCell.h src/DateCell.cpp src/DateCell.h src/FunctionCell.cpp src/FunctionCell.h src/Sheet.cpp src/Sheet.h src/Exp.cpp src/Exp.h src/ExpNode.cpp src/ExpNode.h src/ExpTerm.cpp src/ExpTerm.h src/FormulaCell.cpp src/FormulaCell.h)