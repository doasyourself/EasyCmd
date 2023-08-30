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
    ui->label_warning->hide();
}

CdCmdEditor::~CdCmdEditor()
{
    delete ui;
}

int CdCmdEditor::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDSTRING:
    {
        out_property = getCmdString();
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int CdCmdEditor::setProperty(int propertyId, const QVariant &property)
{
    return 0;
}

QString CdCmdEditor::getCmdString()
{
    // 参数
    QString destPath; // 目标路径
    if (ui->rbtn_localDirpath->isChecked())
    {
        destPath = ui->lineEdit_localDirfilepath->text();
    }
    else
    {
        destPath = "..";
    }

    // 选项
    QString options;
    QStringList optionList;

    if (ui->checkBox_option_d->isChecked())
    {
        optionList << "/d";
    }

    options = optionList.join(" ");

    // 生成命令
    QString cmd;

    QVariant val;
    m_command->getProperty(PID_CMDNAME, val);
    QString cmd_name = val.toString();

    if (options.isEmpty())
    {
        cmd = QString("%1 \"%2\"").arg(cmd_name, destPath);
    }
    else
    {
        cmd = QString("%1 %2 \"%3\"").arg(cmd_name, options, destPath);
    }

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
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void CdCmdEditor::on_checkBox_option_d_toggled(bool checked)
{
    check();
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void CdCmdEditor::on_rbtn_localDirpath_toggled(bool checked)
{
    ui->widget_localDirpath->setEnabled(checked);
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void CdCmdEditor::on_rbtn_relativePath_toggled(bool checked)
{
    ui->widget_relativePath->setEnabled(checked);
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void CdCmdEditor::on_lineEdit_localDirfilepath_textChanged(const QString &text)
{
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

bool CdCmdEditor::check()
{
    bool ok = true;
    if (ui->checkBox_option_d->isChecked())
    {
        if (ui->rbtn_localDirpath->isChecked())
        {
            if (ui->lineEdit_localDirfilepath->text().isEmpty())
            {
                ok = false;
                ui->label_warning->setText("目录不能为空！");
            }
        }
    }

    // 显示提示
    ui->label_warning->setVisible(!ok);
    return ok;
}
