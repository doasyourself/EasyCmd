#include "CdCmdEditor.h"
#include "ui_CdCmdEditor.h"
#include <QFileDialog>

CdCmdEditor::CdCmdEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::CdCmdEditor)
{
    ui->setupUi(this);
}

CdCmdEditor::~CdCmdEditor()
{
    delete ui;
}

bool CdCmdEditor::isModified() const
{
    return true;
}

QString CdCmdEditor::getCmdName()
{
    return "dir";
}

QString CdCmdEditor::getCmdString()
{
    QString options;
    if (ui->checkBox_option_d->isChecked())
    {
        options += " /D";
    }

    QString cmd = getCmdName();
    cmd += QString("%1 \"%2\"").arg(options).arg(ui->lineEdit_dirfilepath->text());
    return cmd;
}

void CdCmdEditor::on_pushButton_selectpath_clicked()
{
    // 用户选择的路径，可以是文件，可以是文件夹
    QString selected_path;

    // 当前路径信息
    QFileInfo fi(ui->lineEdit_dirfilepath->text());

    // 选择文件夹
    if (ui->radioButton_selectDir->isChecked())
    {
        selected_path = QFileDialog::getExistingDirectory(
            this, tr("Choose dest dir"), fi.path(),
            QFileDialog::ShowDirsOnly);
    }
    // 选择文件
    else if (ui->radioButton_selectFile->isChecked())
    {
        selected_path = QFileDialog::getOpenFileName(
            this, tr("Choose dest dir"), fi.path());
    }
    else
    {
        Q_ASSERT_X(0, "CdCmdEditor", "Can't handle this situation.");
    }

    // 更新路径显示
    if (!selected_path.isEmpty())
    {
        // 一定要转成本地分隔符，否则命令行不识别
        ui->lineEdit_dirfilepath->setText(QDir().toNativeSeparators(selected_path));
    }
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
    ui->lineEdit_dirfilepath->setText(native_path);
    emit sigModified();
}

void CdCmdEditor::on_checkBox_option_d_toggled(bool checked)
{
    emit sigModified();
}
