#include "analiticwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnaliticWindow w;
    w.show();

    return a.exec();
}
