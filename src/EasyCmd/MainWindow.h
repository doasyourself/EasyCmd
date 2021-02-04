#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "CmdReadWriteWorker.h"
#include "CmdTreeModel.h"

namespace Ui {
class MainWindow;
}
class QTreeWidgetItem;

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
     * @brief on_pushButton_genCmd_clicked
     *  生成命令按钮响应
     */
    void on_pushButton_genCmd_clicked();

    /**
     * @brief on_action_about_triggered
     *  关于
     */
    void on_action_about_triggered();

    // 实时搜索
    void on_lineEdit_searchCmd_textEdited(const QString &arg1);

private:
    void writeToConsole(QString);
    void moveToScreenCenter();

private:
    Ui::MainWindow *ui;

    // cmd读写
    CmdReadWriteWorker m_rw_worker;

    // 命令行model
    CmdTreeModel *m_cmd_model;
    QSortFilterProxyModel *m_proxy_model;
};

#endif // MAINWINDOW_H
