cmake_minimum_required(VERSION 2.8.4)
project(simple_spreadsheet)

set(CMAKE_CXX_STANDARD 14)

add_executable(simple_spreadsheet src/main.cpp src/cell.cpp src/cell.h src/textCell.cpp src/textCell.h src/sheet.cpp src/sheet.h src/exp.cpp src/exp.h src/expNode.cpp src/expNode.h src/expTerm.cpp src/expTerm.h src/formulaCell.cpp src/formulaCell.h src/expFunction.h src/expFunction.cpp src/sheetView.cpp src/sheetView.h src/sheetController.cpp src/sheetController.h)