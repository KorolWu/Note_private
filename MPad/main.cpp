#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    MettingFrom metting("董事长办公室","智能工厂方案");
//    metting.show();
    return a.exec();
}
