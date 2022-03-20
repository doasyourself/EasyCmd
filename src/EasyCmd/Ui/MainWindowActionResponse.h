#ifndef MAINWINDOWACTIONRESPONSE_H
#define MAINWINDOWACTIONRESPONSE_H

#include <QObject>
#include <QPointer>
#include "MainWindow.h"

class MainWindowActionResponse : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowActionResponse(QObject *parent = nullptr);

private slots:
    void slotGoProjectHomePage(); // 转到项目主页
    void slotGoTeamHomePage(); // 转到团队主页
    void slotFeedback(); // 反馈建议
    void slotCheckUpdate(); // 检查更新

private:
    void init();

private:
    QPointer<MainWindow> m_main;
};

#endif // MAINWINDOWACTIONRESPONSE_H
