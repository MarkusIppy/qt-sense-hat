#ifndef LEDGRIDCONTROLLER_H
#define LEDGRIDCONTROLLER_H
#include <QImage>
class LedGridController
{
    friend class LedGridControllerUT;
public:
    static LedGridController* getInstance();
    void setPixel(int x, int y, QColor color);
private:
    LedGridController();
    ~LedGridController();
    static LedGridController* instance;
    bool init();
    quint16 toRGB565(QColor color);
    quint16* frameBuffer;
};

#endif // LEDGRIDCONTROLLER_H
