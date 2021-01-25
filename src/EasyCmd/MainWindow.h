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

    void on_pushButton_ok_clicked();

    /**
     * @brief slotConsoleOutput
     *  响应输出
     */
    void slotConsoleOutput(QString);

    void on_pushButton_ctrlbreak_clicked();

private:
    void writeToConsole(QString);

private:
    Ui::MainWindow *ui;

    // cmd读写
    CmdReadWriteWorker m_rw_worker;
};

#endif // MAINWINDOW_H
