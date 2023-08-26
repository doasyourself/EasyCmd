#include "RmDirCmdEditor.h"
#include "ui_RmDirCmdEditor.h"
#include <QFileDialog>

RmDirCmdEditor::RmDirCmdEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::RmDirCmdEditor)
{
    ui->setupUi(this);
}

RmDirCmdEditor::~RmDirCmdEditor()
{
    delete ui;
}

bool RmDirCmdEditor::isModified() const
{
    return true;
}

QString RmDirCmdEditor::getCmdName()
{
    return "rmdir";
}

QString RmDirCmdEditor::getCmdString()
{
    QString options;

    QString cmd = getCmdName();
    cmd += QString("%1 \"%2\"").arg(options).arg(ui->lineEdit_arg_dirpath->text());
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
