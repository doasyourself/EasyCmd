#include "CdCmdEditor.h"
#include "ui_CdCmdEditor.h"
#include <QFileDialog>

CdCmdEditor::CdCmdEditor(CdCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::CdCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    // 初始化禁用相对路径
    ui->widget_relativePath->setEnabled(false);
}

CdCmdEditor::~CdCmdEditor()
{
    delete ui;
}

bool CdCmdEditor::isModified() const
{
    return true;
}

QString CdCmdEditor::getCmdString()
{
    QString destPath; // 目标路径
    if (ui->rbtn_localDirpath->isChecked())
    {
        destPath = ui->lineEdit_localDirfilepath->text();
    }
    else
    {
        destPath = "..";
    }

    QString options;
    if (ui->checkBox_option_d->isChecked())
    {
        options += " /D";
    }

    QString cmd = m_command->getCmdName();
    cmd += QString("%1 \"%2\"").arg(options, destPath);
    return cmd;
}

void CdCmdEditor::on_pushButton_selectpath_clicked()
{
    // 用户选择的路径，可以是文件，可以是文件夹
    QString selected_path;

    // 当前路径信息
    QFileInfo fi(ui->lineEdit_localDirfilepath->text());

    // 在当前路径下选择目录
    selected_path = QFileDialog::getExistingDirectory(
        this, tr("Choose dest dir"), fi.path(),
        QFileDialog::ShowDirsOnly);

    // 更新路径显示
    if (!selected_path.isEmpty())
    {
        // 一定要转成本地分隔符，否则命令行不识别
        ui->lineEdit_localDirfilepath->setText(QDir().toNativeSeparators(selected_path));
    }

    // 通知命令改变
    emit sigModified();
}

void CdCmdEditor::on_lineEdit_dirfilepath_textChanged(const QString &dirfilepath)
{
    // 获取本地分隔符样式的路径
    QString native_path = QDir().toNativeSeparators(dirfilepath);

    // 相等就不设置，防止陷入死循环
    if (dirfilepath.compare(native_path) == 0)
    {
        return;
    }

    // 保证是本地
    ui->lineEdit_localDirfilepath->setText(native_path);
    emit sigModified();
}

void CdCmdEditor::on_checkBox_option_d_toggled(bool checked)
{
    emit sigModified();
}

void CdCmdEditor::on_rbtn_localDirpath_toggled(bool checked)
{
    ui->widget_localDirpath->setEnabled(checked);
    emit sigModified();
}

void CdCmdEditor::on_rbtn_relativePath_toggled(bool checked)
{
    ui->widget_relativePath->setEnabled(checked);
    emit sigModified();
}

