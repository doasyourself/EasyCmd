#ifndef UTILS_H
#define UTILS_H

#include <QDateTime>

class QLabel;
class Utils
{
public:
    Utils();

    // 获取源码编译的时间日期
    static QDateTime getCompileDateTime();

    enum TipLevel{
        TL_INFO,/*状态通知*/
        TL_CRITICAL/*错误通知*/
    };
    static void showTip(QLabel *label, const QString &txt, TipLevel tl);
};

#endif // UTILS_H
