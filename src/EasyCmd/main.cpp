#include "MainWindow.h"

#include <QApplication>
#include <QThread>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<QVariantHash>("QVariantHash");

    QString version = QLatin1Literal("V0.2");
    QString application_name = QString("EasyCmd %1（Windows版）")
            .arg(version);
    a.setApplicationName(application_name);
    a.setApplicationVersion(version);

    MainWindow w;
    w.setWindowTitle(application_name);
    w.showMaximized();

    return a.exec();
}
