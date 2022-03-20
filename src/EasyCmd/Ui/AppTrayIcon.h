#ifndef APPTRAYICON_H
#define APPTRAYICON_H

/******************************************************************************
** 系统托盘图标
**
*******************************************************************************/

#include <QObject>
#include <QPointer>

class QMenu;
class QSystemTrayIcon;
class AppTrayIcon : public QObject
{
    Q_OBJECT

public:
    AppTrayIcon(QObject *parent = Q_NULLPTR);
    ~AppTrayIcon();

    /**
     * @brief create
     *  创建托盘
     */
    void create();
    void setMainWindow(QWidget *main_window);
    void createTrayIcon();
    void createTrayMenu();

private:
    QPointer<QWidget> m_mainwindow;
    QSystemTrayIcon *m_tray_icon; // 托盘
    QMenu *m_tray_menu; // 托盘菜单
};

#endif // APPTRAYICON_H
