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
    return "cd";
}

QString CdCmdEditor::getCmdString()
{
    QString options;
    if (ui->checkBox_option_d->isChecked())
    {
        options += " /D";
    }

    QString cmd = getCmdName();
    cmd += QString("%1 \"%2\"").arg(options).arg(ui->lineEdit_arg_dirpath->text());
    return cmd;
}

void CdCmdEditor::on_pushButton_arg_browserDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose dest dir"), ui->lineEdit_arg_dirpath->text());
    if (!dir.isEmpty())
    {
        ui->lineEdit_arg_dirpath->setText(dir);
    }

    emit sigModified();
}

void CdCmdEditor::on_lineEdit_arg_dirpath_textChanged(const QString &dirpath)
{
    emit sigModified();
}

void CdCmdEditor::on_checkBox_option_d_toggled(bool checked)
{
    emit sigModified();
}
