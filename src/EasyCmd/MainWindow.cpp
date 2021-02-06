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
    if (translator.load(":/projectName.qm"))
    {
        qApp->installTranslator(&translator);
    }
    // 加载翻译文件:End

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

    // 响应控制台输出
    connect(&m_rw_worker, SIGNAL(sigOutput(QString)), SLOT(slotConsoleOutput(QString)));

    // 窗口居中显示
    moveToScreenCenter();
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

void MainWindow::slotCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QModelIndex src_current = m_proxy_model->mapToSource(current);

    if (!src_current.parent().isValid() /*不是二级节点*/)
    {
        ui->scrollArea->setWidget(new QWidget);
        return;
    }

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
    connect(editor, &ICmdEditor::sigModified, this, &MainWindow::slotEditorModified);

    // 设置到界面上
    ui->scrollArea->setWidget(editor);

    // 使能按钮
    ui->pushButton_execCmd->setEnabled(true);

    // 清空命令预览
    ui->textEdit_cmdPreview->clear();
}


void MainWindow::writeToConsole(QString cmd_string)
{
    QMetaObject::invokeMethod(&m_rw_worker, "slotWrite", Qt::AutoConnection, Q_ARG(QString, cmd_string));
}

void MainWindow::moveToScreenCenter()
{
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
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
