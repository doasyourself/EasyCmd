#ifndef UTILS_H
#define UTILS_H

#include <QDateTime>

class Utils
{
public:
    Utils();

    // 获取源码编译的时间日期
    static QDateTime getCompileDateTime();
};

#endif // UTILS_H
