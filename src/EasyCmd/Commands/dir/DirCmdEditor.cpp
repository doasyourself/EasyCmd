#include "DirCmdEditor.h"
#include "ui_DirCmdEditor.h"
#include <QFileDialog>

DirCmdEditor::DirCmdEditor(DirCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::DirCmdEditor),
    m_command(command)
{
    ui->setupUi(this);
}

DirCmdEditor::~DirCmdEditor()
{
    delete ui;
}

bool DirCmdEditor::isModified() const
{
    return true;
}

QString DirCmdEditor::getCmdString()
{
    QString options;

    QString cmd = m_command->getCmdName();
    cmd += QString("%1 \"%2\"").arg(options).arg(ui->lineEdit_arg_dirpath->text());
    return cmd;
}

void DirCmdEditor::on_pushButton_arg_browserDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose dest dir"), ui->lineEdit_arg_dirpath->text());
    if (!dir.isEmpty())
    {
        ui->lineEdit_arg_dirpath->setText(dir);
    }

    emit sigModified();
}

void DirCmdEditor::on_lineEdit_arg_dirpath_textChanged(const QString &dirpath)
{
    emit sigModified();
}

void DirCmdEditor::on_checkBox_option_d_toggled(bool checked)
{
    emit sigModified();
}
