#include <iostream>
#include "src/Sheet.h"
#include "src/NumberCell.h"
#include "src/TextCell.h"
#include "src/DateCell.h"

using namespace std;

int main() {
    cout << "Simple spreadsheet v0.0.0.0.0.1" << endl;
    Sheet a("first sheet");
    a.loadSheet("spreadsheet01.csv");
    a.put(3, 3, "=10+10*sin(200)/(3-A2)");
    a.put(1, 1, "20");
    a.put(1, 2, "2das,dma2");
    // print the loaded spreadsheet from the file
    a.printSheet(10, 10, 10, 10);

    return 0;
}