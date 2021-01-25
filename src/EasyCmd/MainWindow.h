#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void slotCurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *);

    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
