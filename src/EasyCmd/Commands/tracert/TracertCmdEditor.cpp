#include "TracertCmdEditor.h"
#include "ui_TracertCmdEditor.h"
#include "Utils.h"

TracertCmdEditor::TracertCmdEditor(TracertCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::TracertCmdEditor),
    m_command(command)
{
    ui->setupUi(this);
    on_checkBox_option_S_toggled(false);
    on_checkBox_option_w_toggled(false);
    on_checkBox_option_h_toggled(false);
    on_checkBox_option_j_toggled(false);
    on_lineEdit_arg_value_targetName_textChanged(ui->lineEdit_arg_value_targetName->text());
}

TracertCmdEditor::~TracertCmdEditor()
{
    delete ui;
}

bool TracertCmdEditor::isModified() const
{
    return true;
}

QString TracertCmdEditor::getCmdString()
{
    QString options;
    if (ui->checkBox_option_d->isChecked())
    {
        options += " -d";
    }

    if (ui->checkBox_option_h->isChecked())
    {
        options += QString(" -h %1").arg(ui->spinBox_option_value_h->value());
    }

    if (ui->checkBox_option_j->isChecked())
    {
        options += QString(" -j %1").arg(ui->lineEdit_option_value_j->text().trimmed());
    }

    if (ui->checkBox_option_w->isChecked())
    {
        options += QString(" -w %1").arg(ui->spinBox_option_value_w->value());
    }

    if (ui->checkBox_option_R->isChecked())
    {
        options += " -R";
    }

    if (ui->checkBox_option_S->isChecked())
    {
        options += QString(" -S \"%1\"").arg(ui->lineEdit_option_value_S->text());
    }

    if (ui->radioButton_option_ipv4->isChecked())
    {
        options += " -4";
    }

    if (ui->radioButton_option_ipv6->isChecked())
    {
        options += " -6";
    }

    QString cmd = QString("%1%2 %3").arg(m_command->getCmdName()).arg(options).arg(ui->lineEdit_arg_value_targetName->text());
    return cmd;
}

void TracertCmdEditor::on_lineEdit_arg_value_targetName_textChanged(const QString &target_name)
{
    if (target_name.isEmpty())
    {
        Utils::showTip(ui->label_targetName_checkinfo, tr("Target can't be empty!"));
    }
    else
    {
        ui->label_targetName_checkinfo->clear();
    }

    emit sigModified();
}

void TracertCmdEditor::on_checkBox_option_d_toggled(bool checked)
{
    emit sigModified();
}

void TracertCmdEditor::on_checkBox_option_h_toggled(bool checked)
{
    ui->spinBox_option_value_h->setEnabled(checked);
    emit sigModified();
}

void TracertCmdEditor::on_checkBox_option_w_toggled(bool checked)
{
    ui->spinBox_option_value_w->setEnabled(checked);
    emit sigModified();
}

void TracertCmdEditor::on_checkBox_option_R_toggled(bool checked)
{
    emit sigModified();
}

void TracertCmdEditor::on_checkBox_option_S_toggled(bool checked)
{
    ui->lineEdit_option_value_S->setEnabled(checked);
    emit sigModified();
}

void TracertCmdEditor::on_radioButton_option_ipv4_toggled(bool checked)
{
    emit sigModified();
}

void TracertCmdEditor::on_radioButton_option_ipv6_toggled(bool checked)
{
    emit sigModified();
}

void TracertCmdEditor::on_lineEdit_option_value_S_textChanged(const QString &arg1)
{
    emit sigModified();
}

void TracertCmdEditor::on_spinBox_option_value_w_valueChanged(int arg1)
{
    emit sigModified();
}

void TracertCmdEditor::on_spinBox_option_value_h_valueChanged(int arg1)
{
    emit sigModified();
}

void TracertCmdEditor::on_checkBox_option_j_toggled(bool checked)
{
    ui->lineEdit_option_value_j->setEnabled(checked);
    emit sigModified();
}

void TracertCmdEditor::on_lineEdit_option_value_j_textChanged(const QString &arg1)
{
    emit sigModified();
}
