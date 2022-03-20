#include "MainWindowActionResponse.h"
#include "ui_MainWindow.h"
#include <QDesktopServices>

MainWindowActionResponse::MainWindowActionResponse(QObject *parent) : QObject(parent)
{
    m_main = qobject_cast<MainWindow *>(parent);
    Q_ASSERT(m_main);

    init();
}

void MainWindowActionResponse::init()
{
    connect(m_main->ui->action_team_homepage, SIGNAL(triggered(bool)), this, SLOT(slotGoTeamHomePage()));
    connect(m_main->ui->action_project_homepage, SIGNAL(triggered(bool)), this, SLOT(slotGoProjectHomePage()));
    connect(m_main->ui->action_feedback, SIGNAL(triggered(bool)), this, SLOT(slotFeedback()));
    connect(m_main->ui->action_check_update, SIGNAL(triggered(bool)), this, SLOT(slotCheckUpdate()));
}


void MainWindowActionResponse::slotGoProjectHomePage()
{
    QUrl url("https://gitee.com/showmework/EasyCmd");
    QDesktopServices::openUrl(url);
}

void MainWindowActionResponse::slotGoTeamHomePage()
{
    QUrl url("www.qtfuture.cn");
    QDesktopServices::openUrl(url);
}

void MainWindowActionResponse::slotFeedback()
{
    QUrl url("https://gitee.com/showmework/EasyCmd");
    QDesktopServices::openUrl(url);
}

void MainWindowActionResponse::slotCheckUpdate()
{
    QUrl url("https://gitee.com/showmework/EasyCmd/releases");
    QDesktopServices::openUrl(url);
}

