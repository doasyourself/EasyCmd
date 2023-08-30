#include "IPConfigCmdEditor.h"
#include "ui_IPConfigCmdEditor.h"

IPConfigCmdEditor::IPConfigCmdEditor(IPConfigCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::IPConfigCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    on_checkBox_setclassid_toggled(false);
    on_checkBox_showclassid_toggled(false);
    on_checkBox_release_toggled(false);
    on_checkBox_renew_toggled(false);

    QList<QCheckBox *> chb_list = findChildren<QCheckBox *>();
    foreach (QCheckBox *chb, chb_list)
    {
        connect(chb, &QCheckBox::toggled, this, &IPConfigCmdEditor::slotOptionChanged);
    }

    // 初始生成一次命令
    genCmdString();
}

IPConfigCmdEditor::~IPConfigCmdEditor()
{
    delete ui;
}

int IPConfigCmdEditor::getProperty(int propertyId, QVariant &out_property)
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

int IPConfigCmdEditor::setProperty(int propertyId, const QVariant &property)
{
    return 0;
}

QString IPConfigCmdEditor::getCmdString()
{
    return m_cmd;
}

void IPConfigCmdEditor::on_checkBox_setclassid_toggled(bool checked)
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

    ui->lineEdit_setclassid->setEnabled(checked);
    ui->lineEdit_newClassid->setEnabled(checked);
}

void IPConfigCmdEditor::on_checkBox_showclassid_toggled(bool checked)
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

    ui->lineEdit_showclassid->setEnabled(checked);
}

void IPConfigCmdEditor::on_checkBox_release_toggled(bool checked)
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

    ui->lineEdit_release->setEnabled(checked);
}

void IPConfigCmdEditor::on_checkBox_renew_toggled(bool checked)
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

    ui->lineEdit_renew->setEnabled(checked);
}

void IPConfigCmdEditor::on_checkBox_all_toggled(bool checked)
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

void IPConfigCmdEditor::on_checkBox_flushdns_toggled(bool checked)
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

void IPConfigCmdEditor::on_checkBox_displaydns_toggled(bool checked)
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

void IPConfigCmdEditor::slotOptionChanged()
{
    genCmdString();
}

void IPConfigCmdEditor::genCmdString()
{
    QVariant val;
    m_command->getProperty(PID_CMDNAME, val);
    QString new_cmd = val.toString();

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
            options += QString(" \"%1\"").arg(adapter);
        }
    }
    else if (ui->checkBox_renew->isChecked())
    {
        options = " /renew";
        QString adapter = ui->lineEdit_renew->text();
        if (!adapter.isEmpty())
        {
            options += QString(" \"%1\"").arg(adapter);
        }
    }
    else if (ui->checkBox_setclassid->isChecked())
    {
        options = " /setclassid";
        QString adapter = ui->lineEdit_setclassid->text();
        if (!adapter.isEmpty())
        {
            options += QString(" \"%1\"").arg(adapter);
        }

        QString new_class_id = ui->lineEdit_newClassid->text();
        if (!new_class_id.isEmpty())
        {
            options += QString(" \"%1\"").arg(new_class_id);
        }
    }
    else if (ui->checkBox_showclassid->isChecked())
    {
        options = " /showclassid";
        QString adapter = ui->lineEdit_showclassid->text();
        if (!adapter.isEmpty())
        {
            options += QString(" \"%1\"").arg(adapter);
        }
    }

    new_cmd += options;

    // 判断命令是否改变
    if (new_cmd != m_cmd)
    {
        m_cmd = new_cmd;
        emit sigNotify(SID_MODIFIED, QVariantHash());
    }
}

void IPConfigCmdEditor::on_lineEdit_setclassid_textChanged(const QString &arg1)
{
    genCmdString();
}

void IPConfigCmdEditor::on_lineEdit_showclassid_textChanged(const QString &arg1)
{
    genCmdString();
}

void IPConfigCmdEditor::on_lineEdit_release_textChanged(const QString &arg1)
{
    genCmdString();
}

void IPConfigCmdEditor::on_lineEdit_renew_textChanged(const QString &arg1)
{
    genCmdString();
}

void IPConfigCmdEditor::on_lineEdit_newClassid_textChanged(const QString &arg1)
{
    genCmdString();
}
