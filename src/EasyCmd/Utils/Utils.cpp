﻿#include "Utils.h"
#include <QLocale>
#include <QLabel>

Utils::Utils()
{

}

QDateTime Utils::getCompileDateTime()
{
    QString date_string = QString::fromLatin1(__DATE__);
    date_string.replace(QRegExp("\\s+"), " ");/*多个空格换成一个空格，因为多次出现空格数不一致的情况*/

    const QDate buildDate = QLocale(QLocale::English).toDate(date_string, "MMM d yyyy");
    const QTime buildTime = QTime::fromString(__TIME__, "hh:mm:ss");

    return QDateTime(buildDate, buildTime);
}

void Utils::showTip(QLabel *label, const QString &txt, Utils::TipLevel tl)
{
    label->show();
    label->setText(txt);
    switch (tl)
    {
    case TL_INFO:
    {
        label->setStyleSheet("color:green;");
        break;
    }
    case TL_CRITICAL:
    {
        label->setStyleSheet("color:red;");
        break;
    }
    default:
    {
        break;
    }
    }
}
