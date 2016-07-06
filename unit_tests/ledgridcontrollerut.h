#ifndef LEDGRIDCONTROLLERUT_H
#define LEDGRIDCONTROLLERUT_H
#include <QObject>

class LedGridControllerUT : public QObject
{
    Q_OBJECT

public:
    LedGridControllerUT();

private Q_SLOTS:
    void failedInit();
    void createSingleton();
    void setPixel();
};
#endif // LEDGRIDCONTROLLERUT_H
