//
// Created by Milan Vu on 2019-06-08.
//

#ifndef SIMPLE_SPREADSHEET_SHEETVIEW_H
#define SIMPLE_SPREADSHEET_SHEETVIEW_H

#include <ncurses.h>
#include <string>
#include "sheet.h"

class SheetView {
public:
    explicit SheetView(Sheet &sheet);

    ~SheetView();

    void drawHeader();

    void drawSheet();

    const std::pair<size_t, size_t> &getFirstCellCoordinates() const;

    static std::string fillHashtags(size_t len);

    static std::string fillSpaces(size_t len);

//    static std::string columnNumberToStr(size_t colNum);

    void updateCellValueView(std::pair<size_t, size_t> cursorPos);

    void writingInCell(std::pair<size_t, size_t> cursorPos, const std::string &str);

    size_t getMaxRow() const;

    size_t getMaxColumn() const;

    Sheet &getSheet();

    WINDOW *getWin();

    void exitSheet();

private:
    size_t maxRow = 80;
    size_t maxColumn = 80;
    size_t cellLen = 8;
    size_t maxInfoCellWidth = 64;
    std::pair<size_t, size_t> firstCellCoordinates = {1 * cellLen, 5};
    std::pair<size_t, size_t> cursorToCoordinates = {20, 0};
    std::pair<size_t, size_t> cursorToFormula = {20, 1};
    std::pair<size_t, size_t> cursorToValue = {20, 2};
    WINDOW *win;
    Sheet sheet;

    static std::string headerLetter(int colNum);

};


#endif //SIMPLE_SPREADSHEET_SHEETVIEW_H
