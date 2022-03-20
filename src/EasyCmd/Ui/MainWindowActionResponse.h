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
    void slotGoProjectHomePage(); // ת����Ŀ��ҳ
    void slotGoTeamHomePage(); // ת���Ŷ���ҳ
    void slotFeedback(); // ��������
    void slotCheckUpdate(); // ������

private:
    void init();

private:
    QPointer<MainWindow> m_main;
};

#endif // MAINWINDOWACTIONRESPONSE_H
