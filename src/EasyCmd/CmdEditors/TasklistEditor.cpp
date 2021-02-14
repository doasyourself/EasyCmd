#include "TasklistEditor.h"
#include "ui_TasklistEditor.h"

TasklistEditor::TasklistEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::TasklistEditor)
{
    ui->setupUi(this);

    on_checkBox_remote_system_toggled(false);
    on_checkBox_option_m_toggled(false);
    on_checkBox_option_fo_toggled(false);
    on_comboBox_option_fo_currentIndexChanged(ui->comboBox_option_fo->currentText());

    // 初始化yin'cang隐藏错误信息提示
    ui->label_info_option_s->hide();
}

TasklistEditor::~TasklistEditor()
{
    delete ui;
}

bool TasklistEditor::isModified() const
{
    return false;
}

QString TasklistEditor::getCmdName()
{
    return "tasklist";
}

QString TasklistEditor::getCmdString()
{
    return m_cmd;
}

void TasklistEditor::on_checkBox_remote_system_toggled(bool checked)
{
    ui->groupBox_remote_system->setEnabled(checked);
}

void TasklistEditor::on_checkBox_option_m_toggled(bool checked)
{
    ui->lineEdit_option_m->setEnabled(checked);

    // 和/svc /v互斥
    if (checked)
    {
        ui->checkBox_option_svc->setChecked(false);
        ui->checkBox_option_v->setChecked(false);
    }
}

void TasklistEditor::on_checkBox_option_v_toggled(bool checked)
{
    // 和/svc /m互斥
    if (checked)
    {
        ui->checkBox_option_svc->setChecked(false);
        ui->checkBox_option_m->setChecked(false);
    }
}

void TasklistEditor::on_checkBox_option_svc_toggled(bool checked)
{
    // 和/m /v互斥
    if (checked)
    {
        ui->checkBox_option_m->setChecked(false);
        ui->checkBox_option_v->setChecked(false);
    }
}

void TasklistEditor::on_comboBox_option_fo_currentIndexChanged(const QString &txt)
{
    // 更新/NH选项状态
    bool is_nh_enable = ui->checkBox_option_fo->isChecked() && (txt == "TABLE" || txt == "CSV");
    ui->checkBox_option_nh->setEnabled(is_nh_enable);
}

void TasklistEditor::on_checkBox_option_fo_toggled(bool checked)
{
    ui->comboBox_option_fo->setEnabled(checked);/*使能复选框*/
    if (checked)
    {
        on_comboBox_option_fo_currentIndexChanged(ui->comboBox_option_fo->currentText()); /*更新/NH选项状态*/
    }
}

void TasklistEditor::on_checkBox_option_fi_toggled(bool checked)
{
    ui->lineEdit_option_fi->setEnabled(checked);
}
