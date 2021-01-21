#include "Device360.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Device360 w;
    w.show();
    return a.exec();
}
