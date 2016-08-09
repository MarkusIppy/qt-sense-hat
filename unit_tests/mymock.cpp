#include "mymock.h"
#include <QTest>
#include <QDebug>
#ifndef UNIT_TEST
#include <sys/mman.h>
#endif

QMap<QString, int> MyMock::intCallsExpected;
QMap<QString, void*> MyMock::ptrCallsExpected;

void MyMock::initMocks()
{
    intCallsExpected.clear();
    ptrCallsExpected.clear();
}

void MyMock::cleanupMocks()
{
    QTest::qCompare(intCallsExpected.size(), 0, "intCallsExpected.size()", "0", __FILE__, __LINE__);
    QTest::qCompare(ptrCallsExpected.size(), 0, "ptrCallsExpected.size()", "0", __FILE__, __LINE__);
}

void MyMock::expectOneCallAndReturnInt(QString functionName, int valueToReturn)
{
    intCallsExpected.insertMulti(functionName, valueToReturn);
}

void MyMock::expectOneCallAndReturnPtr(QString functionName, void* valueToReturn)
{
    ptrCallsExpected.insertMulti(functionName, valueToReturn);
}

int MyMock::returnIntValueForFunction(QString functionName)
{
    if( intCallsExpected.contains(functionName) )
    {
        int returnValue = intCallsExpected.value(functionName);
        intCallsExpected.remove(functionName);
        //qDebug() << "Returned " << returnValue << "for" << functionName;
        return returnValue;
    }
    else
    {
        return -1;
    }
}

void* MyMock::returnPtrValueForFunction(QString functionName)
{
    if( ptrCallsExpected.contains(functionName) )
    {
        void* returnValue = ptrCallsExpected.value(functionName);
        ptrCallsExpected.remove(functionName);
        //qDebug() << "Returned " << returnValue << "for" << functionName;
        return returnValue;
    }
    else
    {
        return (void*)-1;
    }
}

int open_fbdev(const char* device)
{
    QTest::qCompare(QString(device), QString("RPi-Sense FB"), "QString(device)", "QString(\"RPi-Sense FB\")", __FILE__, __LINE__);
    return MyMock::returnIntValueForFunction(QString("open_fbdev"));
}

/*void* mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    QTest::qCompare((void*)addr, (void*)Q_NULLPTR, "addr", "Q_NULLPTR", __FILE__, __LINE__);
    QTest::qCompare((int)length, 128, "lengthint", "128", __FILE__, __LINE__);
    QTest::qCompare(prot, PROT_READ | PROT_WRITE, "prot", "PROT_READ | PROT_WRITE", __FILE__, __LINE__);
    QTest::qCompare(flags, MAP_SHARED, "flags", "MAP_SHARED", __FILE__, __LINE__);
    QTest::qCompare(fd, 42, "fbDevice", "42", __FILE__, __LINE__);
    QTest::qCompare((int)offset, 0, "offset", "0", __FILE__, __LINE__);
    return Q_NULLPTR;
}*/
