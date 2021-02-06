#ifndef ConsoleRwWorker_H
#define ConsoleRwWorker_H

/*******************************************************************************
** 读取进程输出不是采用定时轮询（初始方案），而是响应readyRead立即读取（最终方案）。
** 此对象可以放在单独的线程中。
**
**/

#include <QObject>
#include <QProcess>
#include <QTimer>

class ConsoleRwWorker : public QObject
{
    Q_OBJECT

public:
    ConsoleRwWorker();
    ~ConsoleRwWorker();
    void ctrlBreak();

public slots:
    void slotWrite(QString);
    void slotReadyRead();

signals:
    void sigOutput(QString text);

private:
    QProcess m_cmd_process;
    QTimer m_read_timer;
};

#endif // ConsoleRwWorker_H
