#include "MainWindow.h"
#include <QApplication>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("EasyCmd");
    a.setApplicationVersion("V0.1");

    MainWindow w;
    w.show();

    QProcess::startDetached("osk");

    return a.exec();
}
