#include <iostream>
#include "src/Sheet.h"
#include "src/NumberCell.h"
#include "src/TextCell.h"
#include "src/DateCell.h"

using namespace std;

int main() {
    cout << "This is my spreadsheet implementation." << endl;
    Sheet a;
    a.loadSheet("spreadsheet01.csv");
    a.put(3, 3, NumberCell(10)).put(11, 1, TextCell("hello")).put(10, 20, DateCell(Date(1, 1, 2019)));
    // print the loaded spreadsheet from the file
    a.printSheet(10, 10, 10, 10);

//    b.put(CNumber("A1", 12)).put(CString("B1", "hello"));
//    b.printSheet(1, 2);
//    // should print something like
//    //   |  A  |  B  |
//    //---+-----+-----+
//    // 1 |   12|hello|
//    //---+-----+-----+
//    b.saveSheet("spreadsheet02.csv");
//    b.put(CDate("C1", Date(1, 1, 2016)));
//    b.put(CFunction("C2", "sin", 7));
//    b.put(CFunction("C3", "abs", 7));
//    b.put(CFunction("C4", "concat", 7));
//    assert(toString(*b.getCell("A1")) == "12");
//    b.getCell("A1") = b.getCell("C3") + b.getCell("C2");
    return 0;
}