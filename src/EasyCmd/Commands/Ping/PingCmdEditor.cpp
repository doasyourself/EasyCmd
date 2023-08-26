#include "PingCmdEditor.h"
#include "ui_PingCmdEditor.h"
#include "Utils.h"

PingCmdEditor::PingCmdEditor(PingCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::PingCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    // ��ʼ��
    on_checkBox_option_l_toggled(false);
    on_checkBox_option_i_toggled(false);
    on_checkBox_option_w_toggled(false);

    // �����޸��ź�
    QList<QCheckBox *> checkboxs = findChildren<QCheckBox *>();
    foreach (QCheckBox *chk, checkboxs)
    {
        connect(chk, &QCheckBox::toggled, this, &ICmdEditor::sigModified);
    }

    QList<QSpinBox *> spinboxs = findChildren<QSpinBox *>();
    foreach (QSpinBox *spin, spinboxs)
    {
        connect(spin, QOverload<int>::of(&QSpinBox::valueChanged), this, &ICmdEditor::sigModified);
    }
}

PingCmdEditor::~PingCmdEditor()
{
    delete ui;
}

bool PingCmdEditor::isModified() const
{
    return false;
}

QString PingCmdEditor::getCmdString()
{
    QString cmd_string = m_command->getCmdName();

    // Start: �Ȼ�ȡ������
    QString options;
    if (ui->checkBox_infiniteTimes->isChecked()) /*���޴�*/
    {
        options += " -t"; /*Լ��ǰ����ո���ͬ*/
    }
    else if (ui->checkBox_finiteTimes->isChecked())
    {
        options += " -n " + QString::number(ui->spinBox_times->value());
    }

    if (ui->checkBox_option_a->isChecked())
    {
        options += " -a";
    }

    if (ui->checkBox_option_l->isChecked()) /*С��0Ϊ��Чֵ��������Ĭ��Ϊ-1����Ĭ�ϲ���Ӵ�ѡ���ͬ*/
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

    // ���ip�Ϸ���
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
    emit sigModified();
}

void PingCmdEditor::on_checkBox_infiniteTimes_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_finiteTimes->setChecked(false);/*����*/
    }
}

void PingCmdEditor::on_checkBox_finiteTimes_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_infiniteTimes->setChecked(false);/*����*/
    }
}
