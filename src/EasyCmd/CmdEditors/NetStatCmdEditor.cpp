#include "NetStatCmdEditor.h"
#include "ui_NetStatCmdEditor.h"
#include <QMessageBox>

NetStatCmdEditor::NetStatCmdEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::NetStatCmdEditor)
{
    ui->setupUi(this);

    // 初始化需要设置一次界面
    on_checkBox_option_s_toggled(false);

    // 监听修改操作
    QList<QCheckBox *> checkboxs = findChildren<QCheckBox *>();
    foreach (QCheckBox *chk, checkboxs)
    {
        // 用toggled会有问题，所以这里用clicked
        connect(chk, &QCheckBox::clicked, this, &ICmdEditor::sigModified);
    }

    QList<QSpinBox *> spinboxs = findChildren<QSpinBox *>();
    foreach (QSpinBox *spin, spinboxs)
    {
        connect(spin, QOverload<int>::of(&QSpinBox::valueChanged), this, &ICmdEditor::sigModified);
    }
}

NetStatCmdEditor::~NetStatCmdEditor()
{
    delete ui;
}

bool NetStatCmdEditor::isModified() const
{
    return false;
}

QString NetStatCmdEditor::getCmdName()
{
    return "netstat";
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
        options += " " + ui->spinBox_option_interval->value();
    }
    // End

    QString cmd_string("netstat");
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
