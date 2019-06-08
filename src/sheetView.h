//
// Created by Milan Vu on 2019-06-08.
//

#ifndef SIMPLE_SPREADSHEET_SHEETVIEW_H
#define SIMPLE_SPREADSHEET_SHEETVIEW_H

#include <ncurses.h>
#include <string>
#include "sheet.h"

class SheetView{
public:
    SheetView();
    ~SheetView();

    void initHeader();
    void drawSheet(Sheet &sheet);
    void undoCursor(Sheet &sheet);
    void drawCursor(Sheet &sheet);
    bool validateFormula(std::string formula);
    void parseCell(Cell &cell, int row, int col);
    std::pair<size_t, size_t> getCursor();
    void setCursor(int row, int col);

    char getChar();
    WINDOW* getWin();
    void exitSheet();

private:
    const int MAXrow = 24;
    const int MAXcol = 80;
    const int CellSize = 8;
    std::pair<size_t, size_t> cursor;
    WINDOW *win;

    std::string headerLetter(int colNum);
    std::string formatCell(std::string, const size_t size);

};


#endif //SIMPLE_SPREADSHEET_SHEETVIEW_H
