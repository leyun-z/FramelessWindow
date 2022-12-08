#include "FramelessWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FramelessWindow w;
    w.applyDwmStyle();
    w.show();
    return a.exec();
}
