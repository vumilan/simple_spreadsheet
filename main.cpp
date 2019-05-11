#include <iostream>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "Cell.h"
#include "Sheet.h"

using namespace std;

int main() {
    cout << "This is my spreadsheet implementation." << endl;
    Sheet a;
    a.loadSheet("spreadsheet01.csv");
    // print the loaded spreadsheet from the file
    a.printSheet(10, 10);

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