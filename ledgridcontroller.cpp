#include "ledgridcontroller.h"
#include <QDebug>
#include <QtEndian>
#include <linux/fb.h>
#include <sys/mman.h>

LedGridController* LedGridController::instance = Q_NULLPTR;

typedef struct{
    quint16 pixel[8][8];
} tPixmap;

LedGridController::LedGridController() :
    frameBuffer(Q_NULLPTR)
{
}

LedGridController::~LedGridController()
{
}

LedGridController* LedGridController::getInstance()
{
    if( !instance )
    {
        instance = new LedGridController();
        if( !instance->init() )
        {
            // Framebuffer initialisation failed.
            delete instance;
            instance = Q_NULLPTR;
        }
    }
    return instance;
}

bool LedGridController::init()
{
    int fbDevice = open_fbdev("RPi-Sense FB");
    if (fbDevice <= 0)
    {
        qDebug() << "Framebuffer device open failed.";
        return false;
    }
#ifdef UNIT_TEST
    extern quint8 localBuffer[128];
    frameBuffer = (quint16*)localBuffer;
#else
    frameBuffer = (quint16*)mmap(0, 128, PROT_READ | PROT_WRITE, MAP_SHARED, fbDevice, 0);
    if (!frameBuffer)
    {
        qDebug() << "mmap was unsuccessful.";
        return false;
    }
#endif
    memset((char*)frameBuffer, 0, 128);
    return true;
}

quint16 LedGridController::toRGB565(QColor color)
{
    const quint16 compareValueRBMultiplier = 0x01F; //B0001_1111
    const quint16 compareValueGMultiplier = 0x03F; //B0011_1111
    quint16 returnValue = ((color.red()*compareValueRBMultiplier)/0xFF) << 11;
    returnValue |= ((color.green()*compareValueGMultiplier)/0xFF) << 5;
    returnValue |= (color.blue()*compareValueRBMultiplier)/0xFF;
    return qToBigEndian(returnValue);
}

void LedGridController::setPixel(int x, int y, QColor color)
{
    tPixmap* pixmap = (tPixmap*)frameBuffer;
    pixmap->pixel[y][x] = toRGB565(color);
}
