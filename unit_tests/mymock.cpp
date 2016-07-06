#include "mymock.h"
#include <QTest>
#include <QDebug>

MyMock::~MyMock()
{
    QTest::qCompare(intCallsExpected.size(), 0, "intCallsExpected.size()", "0", __FILE__, __LINE__);
}

void MyMock::expectOneCallAndReturnInt(QString functionName, int valueToReturn)
{
    intCallsExpected.insertMulti(functionName, valueToReturn);
}

int open_fbdev(const char* device)
{
    QTest::qCompare(QString(device), QString("RPi-Sense FB"), "QString(device)", "QString(\"RPi-Sense FB\")", __FILE__, __LINE__);
    return 0;
}
