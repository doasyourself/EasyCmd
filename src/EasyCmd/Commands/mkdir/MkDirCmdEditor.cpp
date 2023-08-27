#include "MkDirCmdEditor.h"
#include "ui_MkDirCmdEditor.h"
#include <QFileDialog>

MkDirCmdEditor::MkDirCmdEditor(MkDirCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::MkDirCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    // 检查参数
    check();
}

MkDirCmdEditor::~MkDirCmdEditor()
{
    delete ui;
}

bool MkDirCmdEditor::isModified() const
{
    return true;
}

QString MkDirCmdEditor::getCmdString()
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

QString MkDirCmdEditor::getOptions()
{
    QString options;
    QStringList optionList;

    if (ui->chbox_help->isChecked())
    {
        optionList << "/?";
    }

    options = optionList.join(" ");
    return options;
}

void MkDirCmdEditor::on_lineEdit_arg_dirpath_textChanged(const QString &dirpath)
{
    emit sigModified();
}

void MkDirCmdEditor::on_checkBox_option_d_toggled(bool checked)
{
    emit sigModified();
}

void MkDirCmdEditor::on_btn_chooseDirpath_clicked()
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

void MkDirCmdEditor::on_chbox_help_toggled(bool checked)
{
    check();

    emit sigModified();
}

bool MkDirCmdEditor::check()
{
    bool ok = true;

    // 无选项时，参数不能为空
    QString options = getOptions();
    if (options.isEmpty())
    {
        if (ui->lineEdit_arg_dirpath->text().isEmpty())
        {
            ui->label_warning->setText("目录不能为空！");
            ok = false;
        }
    }

    ui->label_warning->setVisible(!ok);
    return ok;
}

