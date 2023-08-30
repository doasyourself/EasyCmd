#include "DirCmdEditor.h"
#include "ui_DirCmdEditor.h"
#include <QFileDialog>
#include <tuple>

using namespace std;

DirCmdEditor::DirCmdEditor(DirCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::DirCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    connect(ui->chkbox_option_p, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_q, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_w, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_d, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);

    connect(ui->groupBox_option_a, &QGroupBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_a_d, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_a_h, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_a_s, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_a_l, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_a_d, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_a_r, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_a_a, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_a_i, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);

    connect(ui->groupBox_option_o, &QGroupBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_o_n, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_o_e, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_o_g, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_o_s, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_o_d, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_o_reverse, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);

    connect(ui->groupBox_option_t, &QGroupBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_t_c, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_t_a, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_t_w, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);

    connect(ui->chkbox_option_s, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_b, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_l, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_n, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_x, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_c, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_4, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_r, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
    connect(ui->chkbox_option_help, &QCheckBox::toggled, this, &DirCmdEditor::slot_checkBox_clicked);
}

DirCmdEditor::~DirCmdEditor()
{
    delete ui;
}

QString DirCmdEditor::getCmdString()
{
    // 参数
    QString destPath = ui->lineEdit_arg_dirOrFilepath->text();

    // 选项
    QString options;

    // 生成options
    QStringList optionList;
    if (ui->chkbox_option_p->isChecked())
    {
        optionList << QLatin1String("/p");
    }

    if (ui->chkbox_option_q->isChecked())
    {
        optionList << QLatin1String("/q");
    }

    if (ui->chkbox_option_w->isChecked())
    {
        optionList << QLatin1String("/w");
    }

    if (ui->chkbox_option_d->isChecked())
    {
        optionList << QLatin1String("/d");
    }

    if (ui->groupBox_option_a->isChecked())
    {
        QStringList sub_options;
        if (ui->chkbox_option_a_d->isChecked())
        {
            sub_options << "d";
        }

        if (ui->chkbox_option_a_h->isChecked())
        {
            sub_options << "h";
        }

        if (ui->chkbox_option_a_s->isChecked())
        {
            sub_options << "s";
        }

        if (ui->chkbox_option_a_l->isChecked())
        {
            sub_options << "l";
        }

        if (ui->chkbox_option_a_r->isChecked())
        {
            sub_options << "r";
        }

        if (ui->chkbox_option_a_a->isChecked())
        {
            sub_options << "a";
        }

        if (ui->chkbox_option_a_i->isChecked())
        {
            sub_options << "i";
        }

        QString option_atrribute("/a");
        if (!sub_options.isEmpty())
        {
            option_atrribute.append(":" + sub_options.join(""));
        }

        optionList << option_atrribute;
    }

    if (ui->groupBox_option_o->isChecked())
    {
        QStringList sub_options;
        if (ui->chkbox_option_o_reverse->isChecked())
        {
            sub_options << "-";
        }

        if (ui->chkbox_option_o_n->isChecked())
        {
            sub_options << "n";
        }

        if (ui->chkbox_option_o_e->isChecked())
        {
            sub_options << "e";
        }

        if (ui->chkbox_option_o_g->isChecked())
        {
            sub_options << "g";
        }

        if (ui->chkbox_option_o_s->isChecked())
        {
            sub_options << "s";
        }

        if (ui->chkbox_option_o_d->isChecked())
        {
            sub_options << "d";
        }

        QString option_atrribute("/o");
        if (!sub_options.isEmpty())
        {
            option_atrribute.append(":" + sub_options.join(""));
        }

        optionList << option_atrribute;
    }

    if (ui->groupBox_option_t->isChecked())
    {
        QStringList sub_options;
        if (ui->chkbox_option_t_c->isChecked())
        {
            sub_options << "c";
        }

        if (ui->chkbox_option_t_a->isChecked())
        {
            sub_options << "a";
        }

        if (ui->chkbox_option_t_w->isChecked())
        {
            sub_options << "w";
        }

        QString option_atrribute("/t");
        if (!sub_options.isEmpty())
        {
            option_atrribute.append(":" + sub_options.join(""));
        }

        optionList << option_atrribute;
    }

    if (ui->chkbox_option_s->isChecked())
    {
        optionList << QLatin1String("/s");
    }

    if (ui->chkbox_option_b->isChecked())
    {
        optionList << QLatin1String("/b");
    }

    if (ui->chkbox_option_l->isChecked())
    {
        optionList << QLatin1String("/l");
    }

    if (ui->chkbox_option_n->isChecked())
    {
        optionList << QLatin1String("/n");
    }

    if (ui->chkbox_option_x->isChecked())
    {
        optionList << QLatin1String("/x");
    }

    if (ui->chkbox_option_c->isChecked())
    {
        optionList << QLatin1String("/c");
    }

    if (ui->chkbox_option_4->isChecked())
    {
        optionList << QLatin1String("/4");
    }

    if (ui->chkbox_option_r->isChecked())
    {
        optionList << QLatin1String("/r");
    }

    if (ui->chkbox_option_help->isChecked())
    {
        optionList << QLatin1String("/?");
    }

    options = optionList.join(" ");

    // 生成命令
    QString cmd;

    QVariant val;
    m_command->getProperty(PID_CMDNAME, val);
    QString cmd_name = val.toString();

    if (options.isEmpty())
    {
        cmd = QString("%1 \"%2\"").arg(cmd_name, destPath);
    }
    else
    {
        cmd = QString("%1 %2 \"%3\"").arg(cmd_name, options, destPath);
    }

    return cmd;
}

int DirCmdEditor::getProperty(int propertyId, QVariant &out_property)
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

int DirCmdEditor::setProperty(int propertyId, const QVariant &property)
{
    return 0;
}

void DirCmdEditor::on_lineEdit_arg_dirOrFilepath_textChanged(const QString &dirpath)
{
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

void DirCmdEditor::on_btn_chooseDirpath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose dest dir"),
        ui->lineEdit_arg_dirOrFilepath->text());
    if (!dir.isEmpty())
    {
        ui->lineEdit_arg_dirOrFilepath->setText(QDir::toNativeSeparators(dir));
    }

    emit sigNotify(SID_MODIFIED, QVariantHash());
}


void DirCmdEditor::on_btn_chooseFilepath_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this, tr("Choose dest filepath"),
        ui->lineEdit_arg_dirOrFilepath->text());
    if (!filepath.isEmpty())
    {
        ui->lineEdit_arg_dirOrFilepath->setText(QDir::toNativeSeparators(filepath));
    }

    emit sigNotify(SID_MODIFIED, QVariantHash());
}


void DirCmdEditor::on_btn_resetOptions_clicked()
{
    ui->chkbox_option_p->setChecked(false);
    ui->chkbox_option_q->setChecked(false);
    ui->chkbox_option_w->setChecked(false);
    ui->chkbox_option_d->setChecked(false);

    ui->groupBox_option_a->setChecked(false);
    ui->chkbox_option_a_a->setChecked(false);
    ui->chkbox_option_a_d->setChecked(false);
    ui->chkbox_option_a_h->setChecked(false);
    ui->chkbox_option_a_i->setChecked(false);
    ui->chkbox_option_a_l->setChecked(false);
    ui->chkbox_option_a_r->setChecked(false);
    ui->chkbox_option_a_s->setChecked(false);

    ui->groupBox_option_o->setChecked(false);
    ui->chkbox_option_o_d->setChecked(false);
    ui->chkbox_option_o_e->setChecked(false);
    ui->chkbox_option_o_g->setChecked(false);
    ui->chkbox_option_o_n->setChecked(false);
    ui->chkbox_option_o_s->setChecked(false);
    ui->chkbox_option_o_reverse->setChecked(false);

    ui->groupBox_option_t->setChecked(false);
    ui->chkbox_option_t_a->setChecked(false);
    ui->chkbox_option_t_c->setChecked(false);
    ui->chkbox_option_t_w->setChecked(false);
}

void DirCmdEditor::slot_checkBox_clicked()
{
    emit sigNotify(SID_MODIFIED, QVariantHash());
}

