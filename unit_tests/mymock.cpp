#include "mymock.h"
#include <QTest>
#include <QDebug>

MyMock::~MyMock()
{
    if(intCallsExpected.size() != 0)
    {
        qDebug() << "intCallsExpected had size of" << intCallsExpected.size();
    }
}

void MyMock::expectOneCallAndReturnInt(QString functionName, int valueToReturn)
{
    intCallsExpected.insertMulti(functionName, valueToReturn);
}
