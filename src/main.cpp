#include <iostream>
#include "sheet.h"
#include "textCell.h"
#include "ncurses.h"
#include "sheetView.h"

using namespace std;

Sheet load(const std::string &fileName) {
    std::ifstream file;
    file.open("savedFiles/" + fileName);
    Sheet newSheet(fileName);
    std::string line, token;
    size_t y = 1;
    while (getline(file, line)) { // check every getline
        size_t x = 1, pos;
        // tokenize line
        while ((pos = line.find(';')) != std::string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + 1);
            if (!token.empty())
                newSheet.put(x, y, token);
            ++x;
        }
        ++y;
    }
    return newSheet;
}

int main() {
    cout << "Simple spreadsheet v1.0" << endl;
    Sheet a("first sheet");
    Sheet b = load("sheet1.csv");
//    SheetController().run(b);

    a.put(1, 1, "20");
    a.put(1, 2, "=A1+10");
    a.put(1, 1, "10");
    a.put(1, 3, "=A2+15");
    a.put(1, 4, "=A3+A2+A1");
    a.put(1, 5, "=A4+13");
    a.put(1, 6, "=A5+13+C3");
    a.put(1, 7, "=A4");
    a.put(1, 1, "=A7");
    a.put(1, 1, "LAKATOS");
    a.put(3, 3, "=3*10-20/A1");
    a.put(4, 4, "=20+SIN(A1+2+(2+2))");
    a.put(5, 4, "=CONCAT(A1, 3040, 2+3+SIN(10), kslakad)");
    a.put(4, 5, "=(3+(2))");
    a.put(1, 1, "=20");
    a.put(1, 1, "=");
    a.put(1, 1, "");
    a.put(3, 3, "=CONCAT(E4,A2,CONCAT(E4, E4, E4))");
    // print the loaded spreadsheet from the file
    a.printSheet(10, 10, 10, 10);
    b.printSheet(10, 10, 10, 10);
    a.save("sheet2.csv");
    SheetView().initHeader();
    return 0;
}