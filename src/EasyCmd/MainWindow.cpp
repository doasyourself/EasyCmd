#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CmdEditorHeader.h"
#include "AboutUsDialog.h"
#include "NetStatCmdEditor.h"
#include <QKeyEvent>
#include <QTranslator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // 加载翻译文件:Start
    static QTranslator translator;
    if (translator.load(":/projectName.qm"))
    {
        qApp->installTranslator(&translator);
    }
    // 加载翻译文件:End

    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 5);

    // 初始化禁用生成按钮
    ui->pushButton_genCmd->setEnabled(false);

    // 响应行切换
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
        ui->pushButton_genCmd->setEnabled(false);
        return;
    }

    // 创建对应的编辑器
    QWidget *editor = NULL;
    QString cmd_name = current->text(0);
    if (cmd_name == "ping")
    {
        editor = new PingCmdEditor(ui->scrollArea);
    }
    else if (cmd_name == "netstat")
    {
        editor = new NetStatCmdEditor(ui->scrollArea);
    }

    // 设置到界面上
    ui->scrollArea->setWidget(editor);

    // 使能按钮
    ui->pushButton_genCmd->setEnabled(true);
    ui->pushButton_execCmd->setEnabled(true);
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


void MainWindow::on_pushButton_execCmd_clicked()
{
    QString cmd_string = ui->textEdit_cmdPreview->toPlainText();
    cmd_string.trimmed();
    cmd_string.append("\n");/*保证末尾有\n*/


    // 向cmd.exe写入命令
    writeToConsole(cmd_string);
}

void MainWindow::on_pushButton_genCmd_clicked()
{
    // 清空预览窗
    ui->textEdit_cmdPreview->clear();

    // 生成命令
    QString cmd_string;
    ICmdEditor *editor = dynamic_cast<ICmdEditor *>(ui->scrollArea->widget());
    if (editor)
    {
        cmd_string = editor->getCmdString();
        if (!cmd_string.isEmpty())
        {
            ui->textEdit_cmdPreview->setText(cmd_string);
        }
    }
}

void MainWindow::on_action_about_triggered()
{
    AboutUsDialog dlg;
    dlg.exec();
}
