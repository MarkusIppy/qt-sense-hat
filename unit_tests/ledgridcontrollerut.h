#ifndef LEDGRIDCONTROLLERUT_H
#define LEDGRIDCONTROLLERUT_H
#include <QObject>

class LedGridControllerUT : public QObject
{
    Q_OBJECT

public:
    LedGridControllerUT();

private Q_SLOTS:
    void init();
    void cleanup();
    void failedInit();
    void createSingleton();
    void convertToRgb565();
    void setPixel();
};
#endif // LEDGRIDCONTROLLERUT_H
