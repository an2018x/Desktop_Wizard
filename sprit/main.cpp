#include "sprite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sprite w;
    w.show();

    return a.exec();
}
