#include <QtTest>
#include "ledgridcontrollerut.h"

int main(int argc, char *argv[])
{
    LedGridControllerUT lgcUT;
    QTEST_SET_MAIN_SOURCE_PATH
    int returnValue = QTest::qExec(&lgcUT, argc, argv);
    return returnValue;
}
