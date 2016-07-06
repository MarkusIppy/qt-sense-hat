#include "ledgridcontrollerut.h"
#include "../ledgridcontroller.h"
#include <QtTest>
#include "mymock.h"

LedGridControllerUT::LedGridControllerUT()
{
}

void LedGridControllerUT::failedInit()
{
    MyMock mock;
    QVERIFY(!LedGridController::instance);
    mock.expectOneCallAndReturnInt(QString("open_fbdev"), 0);
    LedGridController *controller = LedGridController::getInstance();
    QVERIFY(!controller);
}

void LedGridControllerUT::createSingleton()
{
    QVERIFY(!LedGridController::instance);
    LedGridController *controller = LedGridController::getInstance();
    QVERIFY(controller);
    QVERIFY(controller == LedGridController::instance);
    LedGridController *controller2 = LedGridController::getInstance();
    QVERIFY(controller2 == controller);
}

void LedGridControllerUT::setPixel()
{
    LedGridController *controller = LedGridController::getInstance();
    controller->setPixel(0,0, QColor(0,0,0));
}
