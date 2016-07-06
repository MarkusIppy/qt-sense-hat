#include "ledgridcontroller.h"
#include <QDebug>
#include <linux/fb.h>

LedGridController* LedGridController::instance = Q_NULLPTR;

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
    /*
    frameBuffer = mmap(0, 128, PROT_READ | PROT_WRITE, MAP_SHARED, fbDevice, 0);
    if (!frameBuffer)
    {
        qDebug() << "mmap was unsuccessful.";
        return false;
    }
    memset(frameBuffer, 0, 128);*/
    return true;
}

void LedGridController::setPixel(int x, int y, QColor color)
{

}
