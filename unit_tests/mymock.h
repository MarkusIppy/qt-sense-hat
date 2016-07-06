#ifndef MYMOCK_H
#define MYMOCK_H
#include <QMap>
#include <QString>

class MyMock
{
public:
    ~MyMock();
    void expectOneCallAndReturnInt(QString functionName, int valueToReturn);
private:
    QMap<QString, int> intCallsExpected;
};

#endif // MYMOCK_H
