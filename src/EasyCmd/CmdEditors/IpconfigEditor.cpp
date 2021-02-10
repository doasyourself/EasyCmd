#include "IpconfigEditor.h"
#include "ui_IpconfigEditor.h"

IpconfigEditor::IpconfigEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::IpconfigEditor)
{
    ui->setupUi(this);

    QList<QCheckBox *> chb_list = findChildren<QCheckBox *>();
    foreach (QCheckBox *chb, chb_list)
    {
        connect(chb, &QCheckBox::toggled, this, &IpconfigEditor::slotOptionChanged);
    }
}

IpconfigEditor::~IpconfigEditor()
{
    delete ui;
}

bool IpconfigEditor::isModified() const
{
    return false;
}

QString IpconfigEditor::getCmdString()
{
    return m_cmd;
}

void IpconfigEditor::on_checkBox_setclassid_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_all->setChecked(false);
        ui->checkBox_displaydns->setChecked(false);
        ui->checkBox_flushdns->setChecked(false);
        ui->checkBox_release->setChecked(false);
        ui->checkBox_renew->setChecked(false);
        ui->checkBox_showclassid->setChecked(false);
    }
}

void IpconfigEditor::on_checkBox_showclassid_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_all->setChecked(false);
        ui->checkBox_displaydns->setChecked(false);
        ui->checkBox_flushdns->setChecked(false);
        ui->checkBox_release->setChecked(false);
        ui->checkBox_renew->setChecked(false);
        ui->checkBox_setclassid->setChecked(false);
    }
}

void IpconfigEditor::on_checkBox_release_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_all->setChecked(false);
        ui->checkBox_displaydns->setChecked(false);
        ui->checkBox_flushdns->setChecked(false);
        ui->checkBox_renew->setChecked(false);
        ui->checkBox_setclassid->setChecked(false);
        ui->checkBox_showclassid->setChecked(false);
    }
}

void IpconfigEditor::on_checkBox_renew_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_all->setChecked(false);
        ui->checkBox_displaydns->setChecked(false);
        ui->checkBox_flushdns->setChecked(false);
        ui->checkBox_release->setChecked(false);
        ui->checkBox_setclassid->setChecked(false);
        ui->checkBox_showclassid->setChecked(false);
    }
}

void IpconfigEditor::on_checkBox_all_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_displaydns->setChecked(false);
        ui->checkBox_flushdns->setChecked(false);
        ui->checkBox_release->setChecked(false);
        ui->checkBox_renew->setChecked(false);
        ui->checkBox_setclassid->setChecked(false);
        ui->checkBox_showclassid->setChecked(false);
    }
}

void IpconfigEditor::on_checkBox_flushdns_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_all->setChecked(false);
        ui->checkBox_displaydns->setChecked(false);
        ui->checkBox_release->setChecked(false);
        ui->checkBox_renew->setChecked(false);
        ui->checkBox_setclassid->setChecked(false);
        ui->checkBox_showclassid->setChecked(false);
    }
}

void IpconfigEditor::on_checkBox_displaydns_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_all->setChecked(false);
        ui->checkBox_flushdns->setChecked(false);
        ui->checkBox_release->setChecked(false);
        ui->checkBox_renew->setChecked(false);
        ui->checkBox_setclassid->setChecked(false);
        ui->checkBox_showclassid->setChecked(false);
    }
}

void IpconfigEditor::slotOptionChanged()
{
    genCmdString();
    emit sigModified();
}

void IpconfigEditor::genCmdString()
{
    m_cmd = "ipconfig";
    QString options;
    if (ui->checkBox_all->isChecked())
    {
        options = " /all";
    }
    else if (ui->checkBox_displaydns->isChecked())
    {
        options = " /displaydns";
    }
    else if (ui->checkBox_flushdns->isChecked())
    {
        options = " /flushdns";
    }
    else if (ui->checkBox_release->isChecked())
    {
        options = " /release";
        QString adapter = ui->lineEdit_release->text();
        if (!adapter.isEmpty())
        {
            options += " " + adapter;
        }
    }
    else if (ui->checkBox_renew->isChecked())
    {
        options = " /renew";
        QString adapter = ui->lineEdit_renew->text();
        if (!adapter.isEmpty())
        {
            options += " " + adapter;
        }
    }
    else if (ui->checkBox_setclassid->isChecked())
    {
        options = " /setclassid";
        QString adapter = ui->lineEdit_setclassid->text();
        if (!adapter.isEmpty())
        {
            options += " " + adapter;
        }
    }
    else if (ui->checkBox_showclassid->isChecked())
    {
        options = " /showclassid";
        QString adapter = ui->lineEdit_showclassid->text();
        if (!adapter.isEmpty())
        {
            options += " " + adapter;
        }
    }

    m_cmd += options;
}
