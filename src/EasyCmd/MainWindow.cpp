#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CmdEditorHeader.h"
#include "AboutUsDialog.h"
#include "NetStatCmdEditor.h"
#include "EditorFactory.h"
#include "CmdProxyModel.h"

#include <QDesktopWidget>
#include <QKeyEvent>
#include <QTranslator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // 加载翻译文件:Start
    static QTranslator translator;
    if (translator.load(":/easycmd.qm"))
    {
        qApp->installTranslator(&translator);
    }
    // 加载翻译文件:End

    // 托盘图标
    qApp->setQuitOnLastWindowClosed(false);

    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 5);

    ui->splitter_2->setStretchFactor(0, 5);
    ui->splitter_2->setStretchFactor(1, 3);

    // 加载命令列表
    m_cmd_model = CmdTreeModel::modelFromFile(":/CommandTree.xml");
    m_proxy_model = new CmdProxyModel;
    m_proxy_model->setSourceModel(m_cmd_model);
    m_proxy_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxy_model->setFilterKeyColumn(-1);
    ui->treeView_cmds->setModel(m_proxy_model);

    // 响应行切换
    connect(ui->treeView_cmds->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &MainWindow::slotCurrentRowChanged);

    // 控制台输入
    connect(ui->textEdit_console, &ConsoleEditor::sigNewInput, this, &MainWindow::writeToConsole);

    // 响应控制台输出
    connect(&m_console_worker, SIGNAL(sigOutput(QString)), SLOT(slotConsoleOutput(QString)));

    // 响应控制台状态和错误
    QProcess *cmd = m_console_worker.getCmdProcess();
    connect(cmd, &QProcess::stateChanged, this, &MainWindow::slotCmdStateChanged);
    connect(cmd, &QProcess::errorOccurred, this, &MainWindow::slotCmdErrorOccurred);

    // 窗口居中显示
    moveToScreenCenter();

    // 创建托盘图标
    m_tray_icon.setMainWindow(this);
    m_tray_icon.create();

    // 启动cmd进程
    m_console_worker.start();
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
            m_console_worker.ctrlBreak();
        }
    }
}

void MainWindow::slotCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QModelIndex src_current = m_proxy_model->mapToSource(current);

    // 获取编辑器id
    QModelIndex first_col_index = m_cmd_model->index(src_current.row(), CmdTreeModel::COL_COMMAND, src_current.parent());
    QString cmd_id = m_cmd_model->data(first_col_index, Qt::UserRole).toString();

    // 如果没填id，就用name
    if (cmd_id.isEmpty())
    {
        cmd_id = m_cmd_model->data(first_col_index).toString();
    }

    // 创建对应的编辑器
    static EditorFactory editor_factory;
    ICmdEditor *editor = editor_factory.createEditor(cmd_id);

    /*找不到编辑器则返回*/
    if (!editor) return;

    /*监听编辑器命令改变信号*/
    connect(editor, &ICmdEditor::sigModified, this, &MainWindow::slotEditorModified);

    /* 更新一次命令，保证当前显示的命令时刻为最新的 */
    QString cmd_string = editor->getCmdString();
    ui->textEdit_cmdPreview->setText(cmd_string);

    // 设置到界面上
    ui->scrollArea->setWidget(editor);

    // 使能按钮
    ui->pushButton_execCmd->setEnabled(true);
}

void MainWindow::writeToConsole(QString cmd_string)
{
    QMetaObject::invokeMethod(&m_console_worker, "slotWrite", Qt::AutoConnection, Q_ARG(QString, cmd_string));
}

void MainWindow::moveToScreenCenter()
{
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

void MainWindow::on_pushButton_ctrlbreak_clicked()
{
    m_console_worker.ctrlBreak();
}

void MainWindow::slotConsoleOutput(QString output)
{
    // 在尾部追加，最后把鼠标移动到尾部
    ui->textEdit_console->appendOuput(output);
}

void MainWindow::on_pushButton_execCmd_clicked()
{
    QString cmd_string = ui->textEdit_cmdPreview->toPlainText();

    cmd_string.trimmed();
    cmd_string.append("\n");/*保证末尾有\n*/

    // 向cmd.exe写入命令
    writeToConsole(cmd_string);
}

void MainWindow::on_action_about_triggered()
{
    AboutUsDialog dlg;
    dlg.exec();
}

void MainWindow::on_lineEdit_searchCmd_textEdited(const QString &arg1)
{
    QString filter_string = ui->lineEdit_searchCmd->text();
    m_proxy_model->setFilterFixedString(filter_string);
}

void MainWindow::slotEditorModified()
{
    ICmdEditor *editor = qobject_cast<ICmdEditor *>(sender());
    QString cmd_string = editor->getCmdString();
    ui->textEdit_cmdPreview->setText(cmd_string);
}

void MainWindow::slotCmdErrorOccurred(QProcess::ProcessError error)
{
    QString error_srting;
    switch (error)
    {
    case QProcess::FailedToStart:
    {
        error_srting = tr("Cmd FailedToStart");
        break;
    }
    case QProcess::Crashed:
    {
        error_srting = tr("Cmd Crashed");
        break;
    }
    case QProcess::Timedout:
    {
        error_srting = tr("Cmd Timedout");
        break;
    }
    case QProcess::ReadError:
    {
        error_srting = tr("Cmd ReadError");
        break;
    }
    case QProcess::WriteError:
    {
        error_srting = tr("Cmd WriteError");
        break;
    }
    case QProcess::UnknownError:
    {
        error_srting = tr("Cmd UnknownError");
        break;
    }
    default:
    {
        break;
    }
    }

    ui->statusBar->showMessage(error_srting);
}

void MainWindow::slotCmdStateChanged(QProcess::ProcessState newState)
{
    QString state_string;
    switch (newState)
    {
    case QProcess::NotRunning:
    {
        state_string = tr("Cmd process NotRunning.");
        break;
    }
    case QProcess::Starting:
    {
        state_string = tr("Cmd process Starting.");
        break;
    }
    case QProcess::Running:
    {
        state_string = tr("Cmd process Running.");
        break;
    }
    default:
    {
        break;
    }
    }

    ui->statusBar->showMessage(state_string);
}











