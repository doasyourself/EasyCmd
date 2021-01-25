#include "Utils.h"
#include <QLocale>

Utils::Utils()
{

}

QDateTime Utils::getCompileDateTime()
{
    QString date_string = QString::fromLatin1(__DATE__);

    const QDate buildDate = QLocale(QLocale::English).toDate(date_string, "MMM d yyyy");
    const QTime buildTime = QTime::fromString(__TIME__, "hh:mm:ss");

    return QDateTime(buildDate, buildTime);
}
