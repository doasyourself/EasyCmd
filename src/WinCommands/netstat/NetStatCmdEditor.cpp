#include "NetStatCmdEditor.h"
#include "ui_NetStatCmdEditor.h"
#include <QMessageBox>

NetStatCmdEditor::NetStatCmdEditor(NetStatCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::NetStatCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    // 初始化需要设置一次界面
    on_checkBox_option_s_toggled(false);
    on_checkBox_option_p_toggled(false);
    on_checkBox_option_interval_toggled(false);

    // 监听修改操作
    QList<QCheckBox *> checkboxs = findChildren<QCheckBox *>();
    foreach (QCheckBox *chk, checkboxs)
    {
        // 用toggled会有问题，所以这里用clicked
        connect(chk, &QCheckBox::clicked, this, &NetStatCmdEditor::slot_checkBox_clicked);
    }

    QList<QSpinBox *> spinboxs = findChildren<QSpinBox *>();
    foreach (QSpinBox *spin, spinboxs)
    {
        connect(spin, QOverload<int>::of(&QSpinBox::valueChanged),
                this, &NetStatCmdEditor::slot_checkBox_clicked);
    }
}

NetStatCmdEditor::~NetStatCmdEditor()
{
    delete ui;
}

int NetStatCmdEditor::getProperty(int propertyId, QVariant &out_property)
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

int NetStatCmdEditor::setProperty(int propertyId, const QVariant &property)
{
    return 0;
}

QString NetStatCmdEditor::getCmdString()
{
    // Start: 获取配置项
    QString options;
    if (ui->checkBox_option_a->isChecked()) /*无限次*/
    {
        options += " -a"; /*约定前面带空格，下同*/
    }

    if (ui->checkBox_option_b->isChecked())
    {
        options += " -b";
    }

    if (ui->checkBox_option_e->isChecked())
    {
        options += " -e";
    }

    if (ui->checkBox_option_f->isChecked())
    {
        options += " -f";
    }

    if (ui->checkBox_options_n->isChecked())
    {
        options += " -n";
    }

    if (ui->checkBox_option_o->isChecked())
    {
        options += " -o";
    }

    if (ui->checkBox_option_q->isChecked())
    {
        options += " -q";
    }

    if (ui->checkBox_option_r->isChecked())
    {
        options += " -r";
    }

    if (ui->checkBox_option_s->isChecked())
    {
        options += " -s";
    }

    if (ui->checkBox_option_p->isChecked())
    {
        options += " -p";
        options += " " + ui->comboBox_option_p->currentText();
    }

    if (ui->checkBox_option_y->isChecked())
    {
        options += " -y";
    }

    if (ui->checkBox_option_x->isChecked())
    {
        options += " -x";
    }

    if (ui->checkBox_option_v->isChecked())
    {
        options += " -v";
    }

    if (ui->checkBox_option_interval->isChecked())
    {
        options += " " + QString::number(ui->spinBox_option_interval->value());
    }
    // End

    QVariant val;
    m_command->getProperty(PID_CMDNAME, val);
    QString cmd_string = val.toString();

    cmd_string += options;
    cmd_string += "\n";
    return cmd_string;
}

void NetStatCmdEditor::on_checkBox_option_s_toggled(bool checked)
{
    // 按照说明实现和-p选项关联
    QStringList protos;
    if (!checked)
    {
        protos << "TCP" << "UDP" << "TCPv6" << "UDPv6";
    }
    else
    {
        protos << "IP" << "IPv6" << "ICMP" << "ICMPv6" << "TCP" << "TCPv6" << "UDP" << "UDPv6";
    }

    ui->comboBox_option_p->clear();
    ui->comboBox_option_p->addItems(protos);
}

void NetStatCmdEditor::on_checkBox_option_p_toggled(bool checked)
{
    ui->comboBox_option_p->setEnabled(checked);
}

void NetStatCmdEditor::on_checkBox_option_interval_toggled(bool checked)
{
    ui->spinBox_option_interval->setEnabled(checked);
}

void NetStatCmdEditor::slot_checkBox_clicked()
{
    emit sigNotify(SID_MODIFIED, QVariantHash());
}
