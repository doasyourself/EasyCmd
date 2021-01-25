#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CmdReadWriteWorker.h"

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
    void slotCurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *);

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

    void on_action_about_triggered();

private:
    void writeToConsole(QString);

private:
    Ui::MainWindow *ui;

    // cmd读写
    CmdReadWriteWorker m_rw_worker;
};

#endif // MAINWINDOW_H
