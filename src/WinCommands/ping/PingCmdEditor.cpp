#include "PingCmdEditor.h"
#include "ui_PingCmdEditor.h"
#include "Utils.h"

PingCmdEditor::PingCmdEditor(PingCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::PingCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    // 初始化
    on_checkBox_option_l_toggled(false);
    on_checkBox_option_i_toggled(false);
    on_checkBox_option_w_toggled(false);

    // 监听修改信号
    QList<QCheckBox *> checkboxs = findChildren<QCheckBox *>();
    foreach (QCheckBox *chk, checkboxs)
    {
        connect(chk, &QCheckBox::toggled, this, &PingCmdEditor::slot_checkBox_clicked);
    }

    QList<QSpinBox *> spinboxs = findChildren<QSpinBox *>();
    foreach (QSpinBox *spin, spinboxs)
    {
        connect(spin, QOverload<int>::of(&QSpinBox::valueChanged),
                this, &PingCmdEditor::slot_checkBox_clicked);
    }
}

PingCmdEditor::~PingCmdEditor()
{
    delete ui;
}

int PingCmdEditor::getProperty(int propertyId, QVariant &out_property)
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

int PingCmdEditor::setProperty(int propertyId, const QVariant &property)
{
    return 0;
}

QString PingCmdEditor::getCmdString()
{
    QVariant val;
    m_command->getProperty(PID_CMDNAME, val);
    QString cmd_name = val.toString();

    QString cmd_string;

    // Start: 先获取配置项
    QString options;
    if (ui->checkBox_infiniteTimes->isChecked()) /*无限次*/
    {
        options += " -t"; /*约定前面带空格，下同*/
    }
    else if (ui->checkBox_finiteTimes->isChecked())
    {
        options += " -n " + QString::number(ui->spinBox_times->value());
    }

    if (ui->checkBox_option_a->isChecked())
    {
        options += " -a";
    }

    if (ui->checkBox_option_l->isChecked()) /*小于0为无效值，界面上默认为-1，即默认不添加此选项，下同*/
    {
        int option_l = ui->spinBox_options_l->value();
        options += " -l " + QString::number(option_l);
    }

    if (ui->checkBox_options_f->isChecked())
    {
        options += " -f";
    }

    if (ui->checkBox_option_i->isChecked())
    {
        int options_i = ui->spinBox_options_i->value();
        options += " -i " + QString::number(options_i);
    }

    if (ui->checkBox_option_w->isChecked())
    {
        int options_w = ui->spinBox_options_w->value();
        options += " -w " + QString::number(options_w);
    }
    // End

    cmd_string += options;

    // 检查ip合法性
    QString ip_url = ui->lineEdit_ip_url->text();
    if (ip_url.isEmpty())
    {
        Utils::showTip(ui->label_info_ip_url, tr("Please input correct ip/url!"), Utils::TL_CRITICAL);
    }
    else
    {
        ui->label_info_ip_url->clear();
        cmd_string += " " + ip_url;
        cmd_string += "\n";
    }

    return cmd_string;
}

void PingCmdEditor::on_checkBox_option_l_toggled(bool checked)
{
    ui->spinBox_options_l->setEnabled(checked);
}

void PingCmdEditor::on_checkBox_option_i_toggled(bool checked)
{
    ui->spinBox_options_i->setEnabled(checked);
}

void PingCmdEditor::on_checkBox_option_w_toggled(bool checked)
{
    ui->spinBox_options_w->setEnabled(checked);
}

void PingCmdEditor::on_lineEdit_ip_url_textChanged(const QString &arg1)
{
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void PingCmdEditor::on_checkBox_infiniteTimes_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_finiteTimes->setChecked(false);/*互斥*/
    }
}

void PingCmdEditor::on_checkBox_finiteTimes_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_infiniteTimes->setChecked(false);/*互斥*/
    }
}

void PingCmdEditor::slot_checkBox_clicked()
{
    emit sigNotify(SID_MODIFIED, QVariantHash());
}
