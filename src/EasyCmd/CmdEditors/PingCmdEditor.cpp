#include "PingCmdEditor.h"
#include "ui_PingCmdEditor.h"
#include <QMessageBox>

PingCmdEditor::PingCmdEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::PingCmdEditor)
{
    ui->setupUi(this);

    // 监听修改信号
    QList<QRadioButton *> radios = findChildren<QRadioButton *>();
    foreach (QRadioButton *radio, radios)
    {
        connect(radio, &QRadioButton::clicked, this, &ICmdEditor::sigModified);
    }

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

QString PingCmdEditor::getCmdName()
{
    return "ping";
}

QString PingCmdEditor::getCmdString()
{
    QString cmd_string("ping");

    // 检查ip合法性
    QString ip_url = ui->lineEdit_ip_url->text();
    if (ip_url.isEmpty())
    {
        QMessageBox::information(this, tr("Info"), tr("Please input correct ip/url!"));
        return cmd_string;
    }

    // Start: 获取配置项
    QString options;
    if (ui->radioButton_infiniteTimes->isChecked()) /*无限次*/
    {
        options += " -t"; /*约定前面带空格，下同*/
    }
    else
    {
        options += " -n" + QString::number(ui->spinBox_times->value());
    }

    if (ui->checkBox_option_a->isChecked())
    {
        options += " -a";
    }

    int option_l = ui->spinBox_options_l->value();
    if (option_l >= 0) /*小于0为无效值，界面上默认为-1，即默认不添加此选项，下同*/
    {
        options += " -l " + QString::number(option_l);
    }

    if (ui->checkBox_options_f->isChecked())
    {
        options += " -f";
    }

    int options_i = ui->spinBox_options_i->value();
    if (options_i >= 0)
    {
        options += " -i " + QString::number(options_i);
    }

    int options_w = ui->spinBox_options_w->value();
    if (options_w >= 0)
    {
        options += " -w " + QString::number(options_w);
    }
    // End

    cmd_string += options;
    cmd_string += " " + ui->lineEdit_ip_url->text();
    cmd_string += "\n";
    return cmd_string;
}
