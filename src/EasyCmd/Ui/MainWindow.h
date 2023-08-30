#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>

#include "ConsoleRwWorker.h"
#include "CmdTreeModel.h"
#include "AppTrayIcon.h"
#include "IUnifiedBase.h"
#include "ICmdEditor.h"

namespace Ui {
class MainWindow;
}
class QTreeWidgetItem;
class QSystemTrayIcon;
class MainWindowActionResponse;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    /**
     * @brief slotCurrentItemChanged
     *  当前行改变消息
     * @param current
     * @param previous
     */
    void slotCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    /**
     * @brief slotConsoleOutput
     *  响应输出
     */
    void slotConsoleOutput(QString);

    /**
     * @brief on_pushButton_ctrlbreak_clicked
     *  中断执行按钮响应
     */
    void on_pushButton_ctrlbreak_clicked();

    /**
     * @brief on_pushButton_execCmd_clicked
     *  执行命令按钮响应
     */
    void on_pushButton_execCmd_clicked();

    /**
     * @brief on_action_about_triggered
     *  关于
     */
    void on_action_about_triggered();

    // 实时搜索
    void on_lineEdit_searchCmd_textEdited(const QString &arg1);

    // 响应编辑器修改信号
    void slotEditorNotify(int type, QVariantHash val);

    // 响应命令行进程错误
    void slotCmdErrorOccurred(QProcess::ProcessError error);

    // 响应命令行进程状态
    void slotCmdStateChanged(QProcess::ProcessState newState);

private:
    void writeToConsole(QString);
    void moveToScreenCenter();

    bool createTrayIcon();
    void createTrayMenu();

private:
    friend class MainWindowActionResponse;
    Ui::MainWindow *ui;

    // cmd读写
    ConsoleRwWorker m_console_worker;

    // 命令行model
    CmdTreeModel *m_cmd_model;
    QSortFilterProxyModel *m_proxy_model;

    // 托盘图标
    AppTrayIcon m_tray_icon;

    // 动作响应
    MainWindowActionResponse *m_action_response;

    /**
     * @brief m_command_cache
     *  命令缓存
     */
    QHash<QString, IUnifiedBase *> m_command_cache;

    /**
     * @brief m_cmd_editor_cache
     *  命令编辑器缓存
     */
    QHash<QString, ICmdEditor*> m_cmd_editor_cache;
};

#endif // MAINWINDOW_H
