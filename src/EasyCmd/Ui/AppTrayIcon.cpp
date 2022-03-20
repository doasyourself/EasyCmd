#include "AppTrayIcon.h"
#include <QIcon>
#include <QAction>
#include <QFile>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>

AppTrayIcon::AppTrayIcon(QObject *parent) :
    QObject(parent)
{

}

AppTrayIcon::~AppTrayIcon()
{
    delete m_tray_menu;
}

void AppTrayIcon::create()
{
    qApp->setQuitOnLastWindowClosed(false);/*设置为显式退出模式*/
    createTrayIcon();
    m_tray_icon->show();
}

void AppTrayIcon::setMainWindow(QWidget *main_window)
{
    m_mainwindow = main_window;
}

void AppTrayIcon::createTrayIcon()
{
    if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        QIcon tray_icon(":/img/logo/logo128.ico");
        m_tray_icon = new QSystemTrayIcon(tray_icon, this);
        m_tray_icon->setToolTip(qApp->applicationDisplayName());
        createTrayMenu();
        m_tray_icon->setContextMenu(m_tray_menu);
    }
}

void AppTrayIcon::createTrayMenu()
{
    m_tray_menu = new QMenu(m_mainwindow);

    QAction *action = new QAction(tr("Open MainWindow"), this);
    connect(action, SIGNAL(triggered(bool)), m_mainwindow, SLOT(show()));
    m_tray_menu->addAction(action);

    m_tray_menu->addSeparator();

    action = new QAction(tr("Exit"), this);
    connect(action, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    m_tray_menu->addAction(action);

    QFile file(":/qss/menu1.qss");
    if (file.open(QIODevice::ReadOnly))
    {
        m_tray_menu->setStyleSheet(file.readAll());
    }
    file.close();
}
