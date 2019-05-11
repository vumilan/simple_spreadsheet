cmake_minimum_required(VERSION 2.8.4)
project(simple_spreadsheet)

set(CMAKE_CXX_STANDARD 14)

add_executable(simple_spreadsheet main.cpp Cell.cpp Cell.h NumberCell.cpp NumberCell.h Date.cpp Date.h TextCell.cpp TextCell.h DateCell.cpp DateCell.h FunctionCell.cpp FunctionCell.h Sheet.cpp Sheet.h)