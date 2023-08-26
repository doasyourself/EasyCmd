/*******************************************************************************
** FI��Filter
** FO: Format
********************************************************************************/

#include "TaskkillCmdEditor.h"
#include "ui_TaskkillCmdEditor.h"
#include "Utils.h"
#include <QStackedLayout>

/*����������*/
enum FilterType
{
    STATUS = 0,
    IMAGENAME,
    PID,
    SESSION,
    CPUTIME,
    MEMUSAGE,
    USERNAME,
    SERVICES,
    WINDOWTITLE,
    MODULES,/**����������ʾ����ģ�飬�������ǹؼ���MODULES**/
};

TaskkillCmdEditor::TaskkillCmdEditor(TaskkillCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::TaskkillCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    // ��ʼ��������
    initFilters();

    // ��ʼ������һ�Σ������л��ź�
    on_groupBox_remote_system_toggled(false);

    // ��ʼ�����ش�����Ϣ��ʾ
    ui->label_info_option_s->hide();
}

TaskkillCmdEditor::~TaskkillCmdEditor()
{
    delete ui;
}

bool TaskkillCmdEditor::isModified() const
{
    return false;
}

QString TaskkillCmdEditor::getCmdString()
{
    QString cmd = m_command->getCmdName();
    QString options;

    do
    {
        // /Sѡ��
        if (ui->groupBox_remote_system->isChecked())
        {
            options += " /S";

            QString hostname = ui->lineEdit_option_s->text();
            if (hostname.isEmpty()) // error occur
            {
                /*���ִ���ҲҪ��������Ȼ��������û᲻��ʾ*/
                Utils::showTip(ui->label_info_option_s, tr("Hostname can't be empty!"));
            }
            else
            {
                ui->label_info_option_s->hide();
                options += " " + hostname;
            }

            QString user = ui->lineEdit_option_u->text();
            if (!user.isEmpty())
            {
                options += " /U " + user;
            }

            QString password = ui->lineEdit_option_p->text();
            if (!password.isEmpty())
            {
                options += " /P " + password;
            }
        }

        // ��������
        options += m_filter_list.join("");

        // ֱ��ָ��PID
        if (ui->radioButton_option_pid->isChecked())
        {
            QString pids = ui->lineEdit_option_value_pid->text();
            QStringList pid_list = pids.split(" ");/*���PID�ÿո�ֿ������ö��ţ���Ϊ����Ӣ�Ķ���֮��*/
            foreach (const QString &pid, pid_list)
            {
                options += QString(" /PID %1").arg(pid);
            }
        }

        // ֱ��ָ��������
        if (ui->radioButton_option_im->isChecked())
        {
            options += QString(" /IM \"%1\"").arg(ui->lineEdit_option_value_im->text());
        }

        // ͬʱ��ֹ�ӽ���
        if (ui->checkBox_option_t->isChecked())
        {
            options += " /T";
        }

        // ǿ����ֹ
        if (ui->checkBox_option_f->isChecked() ||
            ui->groupBox_remote_system->isChecked()/*Զ�̽���ʼ����Ҫǿ����ֹ*/)
        {
            options += " /F";
        }
    } while (0);

    cmd += options;
    return cmd;
}

// �������༭��
void TaskkillCmdEditor::on_lineEdit_option_s_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// �û����༭��
void TaskkillCmdEditor::on_lineEdit_option_u_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// ����༭��
void TaskkillCmdEditor::on_lineEdit_option_p_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

void TaskkillCmdEditor::initFilters()
{
    /************** �жϷ� **************/
    ui->comboBox_op_status->addItem(tr("eq"), "eq");
    ui->comboBox_op_status->addItem(tr("ne"), "ne");

    ui->comboBox_op_imageName->addItem(tr("eq"), "eq");
    ui->comboBox_op_imageName->addItem(tr("ne"), "ne");

    ui->comboBox_op_pid->addItem(tr("eq"), "eq");
    ui->comboBox_op_pid->addItem(tr("ne"), "ne");
    ui->comboBox_op_pid->addItem(tr("gt"), "gt");
    ui->comboBox_op_pid->addItem(tr("lt"), "lt");
    ui->comboBox_op_pid->addItem(tr("ge"), "ge");
    ui->comboBox_op_pid->addItem(tr("le"), "le");

    ui->comboBox_op_session->addItem(tr("eq"), "eq");
    ui->comboBox_op_session->addItem(tr("ne"), "ne");
    ui->comboBox_op_session->addItem(tr("gt"), "gt");
    ui->comboBox_op_session->addItem(tr("lt"), "lt");
    ui->comboBox_op_session->addItem(tr("ge"), "ge");
    ui->comboBox_op_session->addItem(tr("le"), "le");

    ui->comboBox_op_cpuTime->addItem(tr("eq"), "eq");
    ui->comboBox_op_cpuTime->addItem(tr("ne"), "ne");
    ui->comboBox_op_cpuTime->addItem(tr("gt"), "gt");
    ui->comboBox_op_cpuTime->addItem(tr("lt"), "lt");
    ui->comboBox_op_cpuTime->addItem(tr("ge"), "ge");
    ui->comboBox_op_cpuTime->addItem(tr("le"), "le");

    ui->comboBox_op_memusage->addItem(tr("eq"), "eq");
    ui->comboBox_op_memusage->addItem(tr("ne"), "ne");
    ui->comboBox_op_memusage->addItem(tr("gt"), "gt");
    ui->comboBox_op_memusage->addItem(tr("lt"), "lt");
    ui->comboBox_op_memusage->addItem(tr("ge"), "ge");
    ui->comboBox_op_memusage->addItem(tr("le"), "le");

    ui->comboBox_op_userName->addItem(tr("eq"), "eq");
    ui->comboBox_op_userName->addItem(tr("ne"), "ne");

    ui->comboBox_op_service->addItem(tr("eq"), "eq");
    ui->comboBox_op_service->addItem(tr("ne"), "ne");

    ui->comboBox_op_windowTitle->addItem(tr("eq"), "eq");
    ui->comboBox_op_windowTitle->addItem(tr("ne"), "ne");

    ui->comboBox_op_module->addItem(tr("eq"), "eq");
    ui->comboBox_op_module->addItem(tr("ne"), "ne");

    // �����޸Ĳ���
    connect(ui->comboBox_op_status, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->comboBox_op_imageName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->comboBox_op_pid, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->comboBox_op_session, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->comboBox_op_cpuTime, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->comboBox_op_memusage, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->comboBox_op_userName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->comboBox_op_service, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->comboBox_op_windowTitle, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->comboBox_op_module, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);

    // ���뵽��ջ����
    m_op_layout = new QStackedLayout;
    m_op_layout->addWidget(ui->comboBox_op_status);
    m_op_layout->addWidget(ui->comboBox_op_imageName);
    m_op_layout->addWidget(ui->comboBox_op_pid);
    m_op_layout->addWidget(ui->comboBox_op_session);
    m_op_layout->addWidget(ui->comboBox_op_cpuTime);
    m_op_layout->addWidget(ui->comboBox_op_memusage);
    m_op_layout->addWidget(ui->comboBox_op_userName);
    m_op_layout->addWidget(ui->comboBox_op_service);
    m_op_layout->addWidget(ui->comboBox_op_windowTitle);
    m_op_layout->addWidget(ui->comboBox_op_module);
    delete ui->widget_operators->layout();
    ui->widget_operators->setLayout(m_op_layout);

    /************* ɸѡֵ�༭�� ****************/
    // �����޸Ĳ���
    connect(ui->comboBox_fiValue_status, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_imageName, &QLineEdit::textChanged, this, &TaskkillCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_pid, &QLineEdit::textChanged, this, &TaskkillCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_session, &QLineEdit::textChanged, this, &TaskkillCmdEditor::sigModified);
    connect(ui->timeEdit_fiValue_cpuTime, &QTimeEdit::timeChanged, this, &TaskkillCmdEditor::sigModified);
    connect(ui->spinBox_fiValue_memUsage, QOverload<int>::of(&QSpinBox::valueChanged), this, &TaskkillCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_userName, &QLineEdit::textChanged, this, &TaskkillCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_service, &QLineEdit::textChanged, this, &TaskkillCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_windowTitle, &QLineEdit::textChanged, this, &TaskkillCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_module, &QLineEdit::textChanged, this, &TaskkillCmdEditor::sigModified);

    m_fiValue_layout = new QStackedLayout;
    m_fiValue_layout->addWidget(ui->comboBox_fiValue_status);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_imageName);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_pid);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_session);
    m_fiValue_layout->addWidget(ui->timeEdit_fiValue_cpuTime);
    m_fiValue_layout->addWidget(ui->spinBox_fiValue_memUsage);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_userName);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_service);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_windowTitle);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_module);
    delete ui->widget_filterValues->layout();
    ui->widget_filterValues->setLayout(m_fiValue_layout);
}

void TaskkillCmdEditor::setupFilterTypes(bool remote_system)
{
    ui->comboBox_filterType->clear();
    if (remote_system)/*������˵��Զ��ϵͳû��STATUS��WINDOWTITLEѡ��*/
    {
        ui->comboBox_filterType->addItem(tr("IMAGENAME(Process Imagename)"), IMAGENAME);
        ui->comboBox_filterType->addItem(tr("PID(Process ID)"), PID);
        ui->comboBox_filterType->addItem(tr("SESSION(Process Session ID)"), SESSION);
        ui->comboBox_filterType->addItem(tr("CPUTIME(Process CpuTime Usage)"), CPUTIME);
        ui->comboBox_filterType->addItem(tr("MEMUSAGE(Process Memory Usage)"), MEMUSAGE);
        ui->comboBox_filterType->addItem(tr("USERNAME(Process Username)"), USERNAME);
        ui->comboBox_filterType->addItem(tr("SERVICES(Service Name)"), SERVICES);
        ui->comboBox_filterType->addItem(tr("MODULES(Process Modules)"), MODULES);
    }
    else
    {
        ui->comboBox_filterType->addItem(tr("STATUS(Process Status)"), STATUS);
        ui->comboBox_filterType->addItem(tr("IMAGENAME(Process Imagename)"), IMAGENAME);
        ui->comboBox_filterType->addItem(tr("PID(Process ID)"), PID);
        ui->comboBox_filterType->addItem(tr("SESSION(Process Session ID)"), SESSION);
        ui->comboBox_filterType->addItem(tr("CPUTIME(Process CpuTime Usage)"), CPUTIME);
        ui->comboBox_filterType->addItem(tr("MEMUSAGE(Process Memory Usage)"), MEMUSAGE);
        ui->comboBox_filterType->addItem(tr("USERNAME(Process Username)"), USERNAME);
        ui->comboBox_filterType->addItem(tr("SERVICES(Service Name)"), SERVICES);
        ui->comboBox_filterType->addItem(tr("WINDOWTITLE(Process Window Title)"), WINDOWTITLE);
        ui->comboBox_filterType->addItem(tr("MODULES(Process Modules)"), MODULES);
    }
}

void TaskkillCmdEditor::on_comboBox_filterType_currentIndexChanged(int index)
{
    int filter_type = ui->comboBox_filterType->currentData().toInt();
    m_op_layout->setCurrentIndex(filter_type);
    m_fiValue_layout->setCurrentIndex(filter_type);
    emit sigModified();
}

void TaskkillCmdEditor::on_groupBox_remote_system_toggled(bool checked)
{
    if (checked)
    {
        ui->checkBox_option_f->setChecked(true);/*��ֹԶ��ʼ����Ҫǿ����ֹ/F*/
        ui->checkBox_option_f->setEnabled(false);
    }
    else
    {
        ui->checkBox_option_f->setEnabled(true);
    }

    setupFilterTypes(checked);/*���ع���������*/
    m_filter_list.clear();/*��յ�ǰ�������б���*/
    emit sigModified();
}

void TaskkillCmdEditor::on_pushButton_addFilter_clicked()
{
    QString filter_string = QString(" /FI ");

    // �����������
    QString fi_type;
    QString fi_op;
    QString fi_value;
    int filter_type = ui->comboBox_filterType->currentData().toInt();
    switch (filter_type)
    {
    case STATUS:
    {
        fi_type = "STATUS";
        fi_op = ui->comboBox_op_status->currentData().toString();
        fi_value = ui->comboBox_fiValue_status->currentText();
        break;
    }
    case IMAGENAME:
    {
        fi_type = "IMAGENAME";
        fi_op = ui->comboBox_op_imageName->currentData().toString();
        fi_value = ui->lineEdit_fiValue_imageName->text();
        break;
    }
    case PID:
    {
        fi_type = "IMAGENAME";
        fi_op = ui->comboBox_op_pid->currentData().toString();
        fi_value = ui->lineEdit_fiValue_pid->text();
        break;
    }
    case SESSION:
    {
        fi_type = "SESSION";
        fi_op = ui->comboBox_op_session->currentData().toString();
        fi_value = ui->lineEdit_fiValue_session->text();
        break;
    }
    case CPUTIME:
    {
        fi_type = "CPUTIME";
        fi_op = ui->comboBox_op_cpuTime->currentData().toString();
        fi_value = ui->timeEdit_fiValue_cpuTime->text();
        break;
    }
    case MEMUSAGE:
    {
        fi_type = "MEMUSAGE";
        fi_op = ui->comboBox_op_memusage->currentData().toString();
        fi_value = ui->spinBox_fiValue_memUsage->text();
        break;
    }
    case USERNAME:
    {
        fi_type = "USERNAME";
        fi_op = ui->comboBox_op_userName->currentData().toString();
        fi_value = ui->lineEdit_fiValue_userName->text();
        break;
    }
    case SERVICES:
    {
        fi_type = "SERVICES";
        fi_op = ui->comboBox_op_service->currentData().toString();
        fi_value = ui->lineEdit_fiValue_service->text();
        break;
    }
    case WINDOWTITLE:
    {
        fi_type = "WINDOWTITLE";
        fi_op = ui->comboBox_op_windowTitle->currentData().toString();
        fi_value = ui->lineEdit_fiValue_windowTitle->text();
        break;
    }
    case MODULES:
    {
        fi_type = "MODULES";
        fi_op = ui->comboBox_op_module->currentData().toString();
        fi_value = ui->lineEdit_fiValue_module->text();
        break;
    }
    default:
    {
        Q_ASSERT(0);
        break;
    }
    }

    filter_string += QString("\"%1 %2 %3\"").arg(fi_type).arg(fi_op).arg(fi_value);
    m_filter_list.append(filter_string);
    emit sigModified();
}

void TaskkillCmdEditor::on_pushButton_clearFilter_clicked()
{
    m_filter_list.clear();
    emit sigModified();
}

void TaskkillCmdEditor::on_spinBox_option_value_pid_valueChanged(int  checked)
{
    emit sigModified();
}

void TaskkillCmdEditor::on_lineEdit_option_value_im_textChanged(const QString &arg1)
{
    emit sigModified();
}

void TaskkillCmdEditor::on_checkBox_option_t_toggled(bool checked)
{
    emit sigModified();
}

void TaskkillCmdEditor::on_checkBox_option_f_toggled(bool checked)
{
    emit sigModified();
}

void TaskkillCmdEditor::on_radioButton_option_pid_toggled(bool checked)
{
    // /PID��/IMѡ���
    ui->lineEdit_option_value_pid->setEnabled(checked);
    emit sigModified();
}

void TaskkillCmdEditor::on_radioButton_option_im_toggled(bool checked)
{
    // /PID��/IMѡ���
    ui->lineEdit_option_value_im->setEnabled(checked);
    emit sigModified();
}

