#include "SystemToolEditor.h"
#include "ui_SystemToolEditor.h"
#include <QButtonGroup>

SystemToolEditor::SystemToolEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::SystemToolEditor)
{
    ui->setupUi(this);

    // 将所有radiobutton放在一个buttongroup中
    QButtonGroup *btn_group = new QButtonGroup(this);
    QList<QRadioButton *> radio_buttons = findChildren<QRadioButton *>();
    foreach (QRadioButton *btn, radio_buttons)
    {
        btn_group->addButton(btn);
    }
}

SystemToolEditor::~SystemToolEditor()
{
    delete ui;
}

bool SystemToolEditor::isModified() const
{
    return !m_current_cmd.isEmpty();
}

QString SystemToolEditor::getCmdName()
{
    return "";
}

QString SystemToolEditor::getCmdString()
{
    return m_current_cmd;
}

void SystemToolEditor::on_radioButton_servicemsc_clicked()
{
    m_current_cmd = "services.msc";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_notepad_clicked()
{
    m_current_cmd = "notepad.exe";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_cleanmgr_clicked()
{
    m_current_cmd = "cleanmgr";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_compmgmtmsc_clicked()
{
    m_current_cmd = "compmgmt.msc";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_devmgmtmsc_clicked()
{
    m_current_cmd = "devmgmt.msc";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_regedt32_clicked()
{
    m_current_cmd = "regedt32";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_write_clicked()
{
    m_current_cmd = "write";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_mspaint_clicked()
{
    m_current_cmd = "mspaint";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_taskmgr_clicked()
{
    m_current_cmd = "taskmgr";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_charmap_clicked()
{
    m_current_cmd = "charmap";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_magnify_clicked()
{
    m_current_cmd = "magnify";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_mstsc_clicked()
{
    m_current_cmd = "mstsc";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_dxdiag_clicked()
{
    m_current_cmd = "dxdiag";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_controlexe_clicked()
{
    m_current_cmd = "control.exe";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_calc_clicked()
{
    m_current_cmd = "calc";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_explorer_clicked()
{
    m_current_cmd = "explorer";
    emit sigModified();
}

void SystemToolEditor::on_radioButton_systeminfo_toggled(bool checked)
{
    m_current_cmd = "systeminfo";
    emit sigModified();
}
