#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CmdEditorHeader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 4);

    connect(ui->treeWidget_cmds, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(slotCurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *)
{
    if (!current /*未选中*/ || !current->parent() /*不是二级节点*/)
    {
        ui->scrollArea->setWidget(0);
        ui->pushButton_ok->setEnabled(false);
        ui->pushButton_cancel->setEnabled(false);
        return;
    }

    // 创建对应的编辑器
    QWidget *editor = NULL;
    QString cmd_name = current->text(0);
    if (cmd_name == "ping")
    {
        editor = new PingCmdEditor(ui->scrollArea);
    }

    ui->scrollArea->setWidget(editor);
    ui->pushButton_ok->setEnabled(true);
    ui->pushButton_cancel->setEnabled(true);
}

void MainWindow::on_pushButton_ok_clicked()
{
    ICmdEditor *editor = dynamic_cast<ICmdEditor *>(ui->scrollArea->widget());
    if (editor)
    {
        QString cmd_string = editor->getCmdString();
        ui->textBrowser->setText(cmd_string);
    }
}

void MainWindow::on_pushButton_cancel_clicked()
{

}
