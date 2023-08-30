#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CmdEditorHeader.h"
#include "AboutDialog.h"
#include "CommandFactory.h"
#include "CmdProxyModel.h"
#include "MainWindowActionResponse.h"
#include "CommandGlobal.h"

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

    // 响应类
    m_action_response = new MainWindowActionResponse(this);

    // 响应行切换
    connect(ui->treeView_cmds->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &MainWindow::slotCurrentRowChanged);

    // 响应控制台输入
    connect(ui->textEdit_console, &ConsoleEditor::sigNewInput, this, &MainWindow::writeToConsole);
    ui->textEdit_console->setWordWrapMode(QTextOption::NoWrap);/*坚持不换行，否则对表格不友好*/

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

    qDeleteAll(m_command_cache);
    qDeleteAll(m_cmd_editor_cache);
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
    QModelIndex src_previous = m_proxy_model->mapToSource(previous);
    if (src_previous.isValid())
    {
        QModelIndex first_col_index = m_cmd_model->index(src_previous.row(),
            CmdTreeModel::COL_COMMAND, src_previous.parent());
        QString previous_cmd_id = m_cmd_model->data(first_col_index, Qt::UserRole).toString();
        ICmdEditor *previous_editor = m_cmd_editor_cache[previous_cmd_id];
        if (previous_editor)
        {
            // 从scrollarea中取出
            ui->scrollArea->takeWidget();
            previous_editor->setParent(Q_NULLPTR);
            previous_editor->hide();
        }
    }

    // 获取当前命令id
    QModelIndex src_current = m_proxy_model->mapToSource(current);
    QModelIndex first_col_index = m_cmd_model->index(src_current.row(),
        CmdTreeModel::COL_COMMAND, src_current.parent());
    QString cmd_id = m_cmd_model->data(first_col_index, Qt::UserRole).toString();

    // 如果没填id，就用name
    if (cmd_id.isEmpty())
    {
        return;
    }

    // 获取对应的编辑器
    ICmdEditor *editor = Q_NULLPTR;
    QHash<QString, ICmdEditor*>::iterator find_cmd_editor_itor = m_cmd_editor_cache.find(cmd_id);
    if (find_cmd_editor_itor == m_cmd_editor_cache.end())
    {
        static CommandFactory command_factory;

        IUnifiedBase *command = Q_NULLPTR;
        QHash<QString, IUnifiedBase *>::iterator find_it = m_command_cache.find(cmd_id);
        if (find_it == m_command_cache.end())
        {
            command = command_factory.createCommand(cmd_id);
        }
        else
        {
            command = *find_it;
        }

        /*找不到编辑器则返回*/
        if (!command) return;

        // 缓存编辑器
        QVariant val;
        int code = command->getProperty(PID_CMDEDITOR, val);
        Q_ASSERT(code == 0);

        editor = static_cast<ICmdEditor *>(val.value<void *>());
        m_cmd_editor_cache[cmd_id] = editor;

        /*监听编辑器命令改变信号*/
        connect(editor, &ICmdEditor::sigNotify, this, &MainWindow::slotEditorNotify);

        /* 更新一次命令，保证当前显示的命令时刻为最新的 */
        QString cmd_string;
        QVariant cmd_string_val;
        editor->getProperty(PID_CMDSTRING, cmd_string_val);
        cmd_string = cmd_string_val.toString();

        ui->textEdit_cmdPreview->setText(cmd_string);
    }
    else
    {
        // 直接取缓存
        editor = m_cmd_editor_cache[cmd_id];
    }

    // 设置到界面上
    ui->scrollArea->setWidget(editor);
    editor->show();

    // 使能按钮
    ui->pushButton_execCmd->setEnabled(true);
}

void MainWindow::writeToConsole(QString cmd_string)
{
    QMetaObject::invokeMethod(&m_console_worker, "slotWrite", Qt::AutoConnection, Q_ARG(QString, cmd_string));
}

void MainWindow::moveToScreenCenter()
{
    // 考虑多屏幕，在当前屏幕居中，而不是桌面居中
    QDesktopWidget *desktop = qApp->desktop();
    int screen_number = desktop->screenNumber(this);
    QRect rc = desktop->screenGeometry(screen_number);

    move((rc.width() - this->width())/2, (rc.height() - this->height())/2);
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
    AboutDialog dlg;
    dlg.exec();
}

void MainWindow::on_lineEdit_searchCmd_textEdited(const QString &arg1)
{
    QString filter_string = ui->lineEdit_searchCmd->text();
    m_proxy_model->setFilterFixedString(filter_string);
}

void MainWindow::slotEditorNotify(int type, QVariantHash val)
{
    switch (type)
    {
    case SID_MODIFIED:
    {
        ICmdEditor *editor = qobject_cast<ICmdEditor *>(sender());
        QString cmd_string;

        QVariant cmd_string_val;
        editor->getProperty(PID_CMDSTRING, cmd_string_val);
        cmd_string = cmd_string_val.toString();

        ui->textEdit_cmdPreview->setText(cmd_string);
        break;
    }
    default:
    {
        break;
    }
    }
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











