#include "WinSystemToolCmdEditor.h"
#include "ui_WinSystemToolCmdEditor.h"
#include <QButtonGroup>

WinSystemToolCmdEditor::WinSystemToolCmdEditor(WinSystemToolCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::WinSystemToolCmdEditor),
    m_command(command)
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

WinSystemToolCmdEditor::~WinSystemToolCmdEditor()
{
    delete ui;
}

int WinSystemToolCmdEditor::getProperty(int propertyId, QVariant &out_property)
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

int WinSystemToolCmdEditor::setProperty(int propertyId, const QVariant &property)
{
    return 0;
}

QString WinSystemToolCmdEditor::getCmdString()
{
    return m_current_cmd;
}

void WinSystemToolCmdEditor::on_radioButton_servicemsc_clicked()
{
    m_current_cmd = "services.msc";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_notepad_clicked()
{
    m_current_cmd = "notepad.exe";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_cleanmgr_clicked()
{
    m_current_cmd = "cleanmgr";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_compmgmtmsc_clicked()
{
    m_current_cmd = "compmgmt.msc";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_devmgmtmsc_clicked()
{
    m_current_cmd = "devmgmt.msc";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_regedt32_clicked()
{
    m_current_cmd = "regedt32";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_write_clicked()
{
    m_current_cmd = "write";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_mspaint_clicked()
{
    m_current_cmd = "mspaint";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_taskmgr_clicked()
{
    m_current_cmd = "taskmgr";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_charmap_clicked()
{
    m_current_cmd = "charmap";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_magnify_clicked()
{
    m_current_cmd = "magnify";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_mstsc_clicked()
{
    m_current_cmd = "mstsc";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_dxdiag_clicked()
{
    m_current_cmd = "dxdiag";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_controlexe_clicked()
{
    m_current_cmd = "control.exe";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_calc_clicked()
{
    m_current_cmd = "calc";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_explorer_clicked()
{
    m_current_cmd = "explorer";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void WinSystemToolCmdEditor::on_radioButton_systeminfo_toggled(bool checked)
{
    m_current_cmd = "systeminfo";
    emit sigNotify(SID_MODIFIED, QVariantHash());
}
