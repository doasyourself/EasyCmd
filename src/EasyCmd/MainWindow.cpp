#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CmdEditorHeader.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 4);

    connect(ui->treeWidget_cmds, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(slotCurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));

    // 响应控制台输出
    connect(&m_rw_worker, SIGNAL(sigOutput(QString)), SLOT(slotConsoleOutput(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    Qt::KeyboardModifiers modifiers = event->modifiers();
    int key = event->key();

    if (modifiers & Qt::ControlModifier)
    {
        if (key == Qt::Key_C) /*处理Ctrl Break*/
        {
            m_rw_worker.ctrlBreak();
        }
    }
}

void MainWindow::slotCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *)
{
    if (!current /*未选中*/ || !current->parent() /*不是二级节点*/)
    {
        ui->scrollArea->setWidget(0);
        ui->pushButton_ok->setEnabled(false);
        return;
    }

    // 创建对应的编辑器
    QWidget *editor = NULL;
    QString cmd_name = current->text(0);
    if (cmd_name == "ping")
    {
        editor = new PingCmdEditor(ui->scrollArea);
    }

    // 设置到界面上
    ui->scrollArea->setWidget(editor);
    ui->pushButton_ok->setEnabled(true);
}

void MainWindow::on_pushButton_ok_clicked()
{
    ICmdEditor *editor = dynamic_cast<ICmdEditor *>(ui->scrollArea->widget());
    if (editor)
    {
        QString cmd_string = editor->getCmdString();
        if (!cmd_string.isEmpty())
        {
            // 写入命令
            writeToConsole(cmd_string);
        }
    }
}

void MainWindow::slotConsoleOutput(QString output)
{
    // 在尾部追加，最后把鼠标移动到尾部
    ui->plainTextEdit->moveCursor(QTextCursor::End);
    ui->plainTextEdit->insertPlainText(output);
    ui->plainTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::writeToConsole(QString cmd_string)
{
    QMetaObject::invokeMethod(&m_rw_worker, "slotWrite", Qt::AutoConnection, Q_ARG(QString, cmd_string));
}

void MainWindow::on_pushButton_ctrlbreak_clicked()
{
    m_rw_worker.ctrlBreak();
}

void MainWindow::slotConsoleOutput(QString output)
{
    // 在尾部追加，最后把鼠标移动到尾部
    ui->plainTextEdit->moveCursor(QTextCursor::End);
    ui->plainTextEdit->insertPlainText(output);
    ui->plainTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::writeToConsole(QString cmd_string)
{
    QMetaObject::invokeMethod(&m_rw_worker, "slotWrite", Qt::AutoConnection, Q_ARG(QString, cmd_string));
}

void MainWindow::on_pushButton_ctrlbreak_clicked()
{
    m_rw_worker.ctrlBreak();
}
