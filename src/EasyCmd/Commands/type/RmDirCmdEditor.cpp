#include "RmDirCmdEditor.h"
#include "ui_RmDirCmdEditor.h"
#include <QFileDialog>

RmDirCmdEditor::RmDirCmdEditor(RmDirCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::RmDirCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    check();
}

RmDirCmdEditor::~RmDirCmdEditor()
{
    delete ui;
}

bool RmDirCmdEditor::isModified() const
{
    return true;
}

QString RmDirCmdEditor::getCmdString()
{
    // 参数
    QString destPath = ui->lineEdit_arg_dirpath->text();

    // 选项
    QString options = getOptions();

    // 生成命令
    QString cmd;
    if (options.isEmpty())
    {
        cmd = QString("%1 \"%2\"").arg(m_command->getCmdName(), destPath);
    }
    else
    {
        cmd = QString("%1 %2 \"%3\"").arg(m_command->getCmdName(), options, destPath);
    }

    return cmd;
}

void RmDirCmdEditor::on_lineEdit_arg_dirpath_textChanged(const QString &dirpath)
{
    emit sigModified();
}

void RmDirCmdEditor::on_checkBox_option_d_toggled(bool checked)
{
    emit sigModified();
}

void RmDirCmdEditor::on_btn_chooseDirpath_clicked()
{
    // 用户选择的目录路径
    QString selected_path;

    // 当前路径信息
    QFileInfo fi(ui->lineEdit_arg_dirpath->text());

    // 在当前路径下选择目录
    selected_path = QFileDialog::getExistingDirectory(
        this, tr("Choose dest dir"), fi.path(),
        QFileDialog::ShowDirsOnly);

    // 更新路径显示
    if (!selected_path.isEmpty())
    {
        // 一定要转成本地分隔符，否则命令行不识别
        ui->lineEdit_arg_dirpath->setText(QDir().toNativeSeparators(selected_path));
    }

    // 通知命令改变
    emit sigModified();
}

QString RmDirCmdEditor::getOptions()
{
    QString options;
    QStringList optionList;

    if (ui->chbox_option_s->isChecked())
    {
        optionList << "/s";
    }

    if (ui->chbox_option_q->isChecked())
    {
        optionList << "/q";
    }

    if (ui->chBox_option_help->isChecked())
    {
        optionList << "/?";
    }

    options = optionList.join(" ");
    return options;
}

bool RmDirCmdEditor::check()
{
    bool ok = true;

    QString options = getOptions();

    if (options.isEmpty())
    {
        if (ui->lineEdit_arg_dirpath->text().isEmpty())
        {
            ok = false;
            ui->label_warning->setText("目录不能为空！");
        }
    }

    ui->label_warning->setVisible(!ok);

    return ok;
}


void RmDirCmdEditor::on_chbox_option_s_toggled(bool checked)
{
    check();
    emit sigModified();
}


void RmDirCmdEditor::on_chbox_option_q_toggled(bool checked)
{
    check();
    emit sigModified();
}


void RmDirCmdEditor::on_chBox_option_help_toggled(bool checked)
{
    check();
    emit sigModified();
}

