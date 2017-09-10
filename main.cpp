#include "UnitTestForSequence.h"
#include "ListSequence.h"
#include "ArraySequence.h"
#include <fstream>


int main() {
    std::ofstream logFile("TestLog.txt", std::ios_base::app);
    if (logFile) {
        UnitTestForSequence<ListSequence<int>> test1;
        test1.fullTest();
        test1.printLog(logFile);

        UnitTestForSequence<ArraySequence<int>> test2;
        test2.fullTest();
        test2.printLog(logFile);
    }
    return 0;
}
