#include "MkDirCmdEditor.h"
#include "ui_MkDirCmdEditor.h"
#include <QFileDialog>

MkDirCmdEditor::MkDirCmdEditor(MkDirCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::MkDirCmdEditor),
    m_command(command)
{
    ui->setupUi(this);
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
    QString options;

    QString cmd = m_command->getCmdName();
    cmd += QString("%1 \"%2\"").arg(options).arg(ui->lineEdit_arg_dirpath->text());
    return cmd;
}

void MkDirCmdEditor::on_lineEdit_arg_dirpath_textChanged(const QString &dirpath)
{
    emit sigModified();
}

void MkDirCmdEditor::on_checkBox_option_d_toggled(bool checked)
{
    emit sigModified();
}
