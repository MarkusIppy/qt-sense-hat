#ifndef MYMOCK_H
#define MYMOCK_H
#include <QMap>
#include <QString>

class MyMock
{
public:
    static void initMocks();
    static void cleanupMocks();
    static void expectOneCallAndReturnInt(QString functionName, int valueToReturn);
    static void expectOneCallAndReturnPtr(QString functionName, void* valueToReturn);
    static int returnIntValueForFunction(QString functionName);
    static void* returnPtrValueForFunction(QString functionName);
private:
    static QMap<QString, int> intCallsExpected;
    static QMap<QString, void*> ptrCallsExpected;
};

#endif // MYMOCK_H
