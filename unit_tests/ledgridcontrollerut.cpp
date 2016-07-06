#include "ledgridcontrollerut.h"
#include "../ledgridcontroller.h"
#include <QtTest>
#include "mymock.h"
#include <QtEndian>

quint8 localBuffer[128];

LedGridControllerUT::LedGridControllerUT()
{
}

void LedGridControllerUT::init()
{
    MyMock::initMocks();
    memset(localBuffer, -1, 128);
}

void LedGridControllerUT::cleanup()
{
    MyMock::cleanupMocks();
    delete LedGridController::instance;
    LedGridController::instance = Q_NULLPTR;
}


void LedGridControllerUT::failedInit()
{
    QVERIFY(!LedGridController::instance);
    MyMock::expectOneCallAndReturnInt(QString("open_fbdev"), 0);
    LedGridController *controller = LedGridController::getInstance();
    QVERIFY(!controller);
    QVERIFY(!LedGridController::instance);
}

void LedGridControllerUT::createSingleton()
{
    QVERIFY(!LedGridController::instance);
    MyMock::expectOneCallAndReturnInt(QString("open_fbdev"), 1);
    LedGridController *controller = LedGridController::getInstance();
    QVERIFY(controller);
    QVERIFY(controller == LedGridController::instance);
    quint8* verifyPtr = (quint8*)controller->frameBuffer;
    QVERIFY(verifyPtr);
    for( int pos = 0 ; pos < 128 ; pos++)
    {
        QCOMPARE((int)(verifyPtr[pos]), 0);
    }
    LedGridController *controller2 = LedGridController::getInstance();
    QVERIFY(controller2 == controller);
}

void LedGridControllerUT::convertToRgb565()
{
    MyMock::expectOneCallAndReturnInt(QString("open_fbdev"), 1);
    LedGridController *controller = LedGridController::getInstance();
    quint16 bigEndianValue = controller->toRGB565(QColor(0,0,0));
    QCOMPARE(qFromBigEndian(bigEndianValue), (quint16)0);
    bigEndianValue = controller->toRGB565(QColor(0xFF,0xFF,0xFF));
    QCOMPARE(qFromBigEndian(bigEndianValue), (quint16)0xFFFF);
    bigEndianValue = controller->toRGB565(QColor(0x40,0x80,0xC0));
    const quint16 compareValueRBMultiplier = 0x01F; //B0001_1111
    const quint16 compareValueGMultiplier = 0x03F; //B0011_1111
    quint16 compareValue = (0xC0*compareValueRBMultiplier)/0xFF; //blue
    compareValue |= (((0x40*compareValueRBMultiplier)/0xFF) << 11); //red
    compareValue |= (((0x80*compareValueGMultiplier)/0xFF) << 5); //green
    QCOMPARE(qFromBigEndian(bigEndianValue), (quint16)compareValue);
}

void LedGridControllerUT::setPixel()
{
    MyMock::expectOneCallAndReturnInt(QString("open_fbdev"), 1);
    LedGridController *controller = LedGridController::getInstance();
    controller->setPixel(0,0, QColor(0x80,0x0,0xFF));
    QCOMPARE(controller->frameBuffer[0], qToBigEndian((quint16)0x781F));
    controller->setPixel(3,4, QColor(0xFF,0xFF,0xFF));
    QCOMPARE(controller->frameBuffer[(4*8)+3], qToBigEndian((quint16)0xFFFF));
}
