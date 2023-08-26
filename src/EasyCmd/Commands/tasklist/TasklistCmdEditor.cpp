/*******************************************************************************
** FI：Filter
** FO: Format
********************************************************************************/

#include "TasklistCmdEditor.h"
#include "ui_TasklistCmdEditor.h"
#include "Utils.h"
#include <QStackedLayout>

/*过滤器类型*/
enum FilterType
{
    STATUS = 0,
    IMAGENAME,
    PID,
    SESSION,
    SESSIONNAME,
    CPUTIME,
    MEMUSAGE,
    USERNAME,
    SERVICES,
    WINDOWTITLE,
    MODULES,/**帮助里面显示的是模块，经测试是关键字MODULES**/
};

TasklistCmdEditor::TasklistCmdEditor(TasklistCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::TasklistCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    // 初始化过滤器
    initFilters();

    // 初始化调用一次
    on_groupBox_remote_system_toggled(false);
    on_checkBox_option_m_toggled(false);
    on_checkBox_option_fo_toggled(false);
    on_comboBox_option_fo_currentIndexChanged(ui->comboBox_option_fo->currentText());

    // 初始化隐藏错误信息提示
    ui->label_info_option_s->hide();
}

TasklistCmdEditor::~TasklistCmdEditor()
{
    delete ui;
}

bool TasklistCmdEditor::isModified() const
{
    return false;
}

QString TasklistCmdEditor::getCmdString()
{
    QString cmd = m_command->getCmdName();
    QString options;

    do
    {
        // /S选项
        if (ui->groupBox_remote_system->isChecked())
        {
            options += " /S";

            QString hostname = ui->lineEdit_option_s->text();
            if (hostname.isEmpty()) // error occur
            {
                /* 有错误也要继续，否则会导致后面的配置不显示*/
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

        // 模块过滤
        if (ui->checkBox_option_m->isChecked())
        {
            options += " /M";

            // 模块名
            QString mod_name = ui->lineEdit_option_m->text();
            if (!mod_name.isEmpty())
            {
                options += QString("\"%1\"").arg(mod_name);
            }
        }

        // 显示服务
        if (ui->checkBox_option_svc->isChecked())
        {
            options += QString(" /SVC");
        }

        // 显示详细信息
        if (ui->checkBox_option_v->isChecked())
        {
            options += " /V";
        }

        // 过滤条件
        options += m_filter_list.join("");

        // 设置输出格式
        if (ui->checkBox_option_fo->isChecked())
        {
            options += " /FO " + ui->comboBox_option_fo->currentText();
        }

        if (ui->checkBox_option_nh->isChecked())
        {
            options += " /NH";
        }
    } while (0);

    cmd += options;
    return cmd;
}

void TasklistCmdEditor::on_checkBox_option_m_toggled(bool checked)
{
    ui->lineEdit_option_m->setEnabled(checked);

    // 和/svc /v互斥
    if (checked)
    {
        ui->checkBox_option_svc->setChecked(false);
        ui->checkBox_option_v->setChecked(false);
        emit sigModified();
    }
}

// 显示详细信息
void TasklistCmdEditor::on_checkBox_option_v_toggled(bool checked)
{
    // 和/svc /m互斥
    if (checked)
    {
        ui->checkBox_option_svc->setChecked(false);
        ui->checkBox_option_m->setChecked(false);
        emit sigModified();
    }
}

// 显示服务
void TasklistCmdEditor::on_checkBox_option_svc_toggled(bool checked)
{
    // 和/m /v互斥
    if (checked)
    {
        ui->checkBox_option_m->setChecked(false);
        ui->checkBox_option_v->setChecked(false);
        emit sigModified();
    }
}

// 格式改变
void TasklistCmdEditor::on_comboBox_option_fo_currentIndexChanged(const QString &txt)
{
    // 更新/NH选项状态
    bool is_nh_enable = (txt == "TABLE" || txt == "CSV");
    ui->checkBox_option_nh->setEnabled(is_nh_enable);
    emit sigModified();
}

// 输出格式选项
void TasklistCmdEditor::on_checkBox_option_fo_toggled(bool checked)
{
    ui->comboBox_option_fo->setEnabled(checked);/*使能复选框*/
    if (checked)
    {
        on_comboBox_option_fo_currentIndexChanged(ui->comboBox_option_fo->currentText()); /*更新/NH选项状态*/
    }
}

// 主机名编辑框
void TasklistCmdEditor::on_lineEdit_option_s_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// 用户名编辑框
void TasklistCmdEditor::on_lineEdit_option_u_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// 密码编辑框
void TasklistCmdEditor::on_lineEdit_option_p_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// 运行模块筛选
void TasklistCmdEditor::on_lineEdit_option_m_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// 无表头选项
void TasklistCmdEditor::on_checkBox_option_nh_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit sigModified();
}

void TasklistCmdEditor::initFilters()
{
    /************** 判断符 **************/
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

    ui->comboBox_op_sessionName->addItem(tr("eq"), "eq");
    ui->comboBox_op_sessionName->addItem(tr("ne"), "ne");

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

    // 监听修改操作
    connect(ui->comboBox_op_status, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_imageName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_pid, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_session, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_sessionName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_cpuTime, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_memusage, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_userName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_service, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_windowTitle, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->comboBox_op_module, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);

    // 加入到堆栈布局
    m_op_layout = new QStackedLayout;
    m_op_layout->addWidget(ui->comboBox_op_status);
    m_op_layout->addWidget(ui->comboBox_op_imageName);
    m_op_layout->addWidget(ui->comboBox_op_pid);
    m_op_layout->addWidget(ui->comboBox_op_session);
    m_op_layout->addWidget(ui->comboBox_op_sessionName);
    m_op_layout->addWidget(ui->comboBox_op_cpuTime);
    m_op_layout->addWidget(ui->comboBox_op_memusage);
    m_op_layout->addWidget(ui->comboBox_op_userName);
    m_op_layout->addWidget(ui->comboBox_op_service);
    m_op_layout->addWidget(ui->comboBox_op_windowTitle);
    m_op_layout->addWidget(ui->comboBox_op_module);
    delete ui->widget_operators->layout();
    ui->widget_operators->setLayout(m_op_layout);

    /************* 筛选值编辑器 ****************/
    // 监听修改操作
    connect(ui->comboBox_fiValue_status, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_imageName, &QLineEdit::textChanged, this, &TasklistCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_pid, &QLineEdit::textChanged, this, &TasklistCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_session, &QLineEdit::textChanged, this, &TasklistCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_sessionName, &QLineEdit::textChanged, this, &TasklistCmdEditor::sigModified);
    connect(ui->timeEdit_fiValue_cpuTime, &QTimeEdit::timeChanged, this, &TasklistCmdEditor::sigModified);
    connect(ui->spinBox_fiValue_memUsage, QOverload<int>::of(&QSpinBox::valueChanged), this, &TasklistCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_userName, &QLineEdit::textChanged, this, &TasklistCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_service, &QLineEdit::textChanged, this, &TasklistCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_windowTitle, &QLineEdit::textChanged, this, &TasklistCmdEditor::sigModified);
    connect(ui->lineEdit_fiValue_module, &QLineEdit::textChanged, this, &TasklistCmdEditor::sigModified);

    m_fiValue_layout = new QStackedLayout;
    m_fiValue_layout->addWidget(ui->comboBox_fiValue_status);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_imageName);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_pid);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_session);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_sessionName);
    m_fiValue_layout->addWidget(ui->timeEdit_fiValue_cpuTime);
    m_fiValue_layout->addWidget(ui->spinBox_fiValue_memUsage);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_userName);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_service);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_windowTitle);
    m_fiValue_layout->addWidget(ui->lineEdit_fiValue_module);
    delete ui->widget_filterValues->layout();
    ui->widget_filterValues->setLayout(m_fiValue_layout);
}

void TasklistCmdEditor::setupFilterTypes(bool remote_system)
{
    ui->comboBox_filterType->clear();/*清空列表重新加载*/

    if (remote_system)/*帮助中说，远程系统没有STATUS和WINDOWTITLE选项*/
    {
        ui->comboBox_filterType->addItem(tr("IMAGENAME(Process Imagename)"), IMAGENAME);
        ui->comboBox_filterType->addItem(tr("PID(Process ID)"), PID);
        ui->comboBox_filterType->addItem(tr("SESSION(Process Session ID)"), SESSION);
        ui->comboBox_filterType->addItem(tr("SESSIONNAME(Process Session Name)"), SESSIONNAME);
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
        ui->comboBox_filterType->addItem(tr("SESSIONNAME(Process Session Name)"), SESSIONNAME);
        ui->comboBox_filterType->addItem(tr("CPUTIME(Process CpuTime Usage)"), CPUTIME);
        ui->comboBox_filterType->addItem(tr("MEMUSAGE(Process Memory Usage)"), MEMUSAGE);
        ui->comboBox_filterType->addItem(tr("USERNAME(Process Username)"), USERNAME);
        ui->comboBox_filterType->addItem(tr("SERVICES(Service Name)"), SERVICES);
        ui->comboBox_filterType->addItem(tr("WINDOWTITLE(Process Window Title)"), WINDOWTITLE);
        ui->comboBox_filterType->addItem(tr("MODULES(Process Modules)"), MODULES);
    }
}

// 过滤器类型切换响应
void TasklistCmdEditor::on_comboBox_filterType_currentIndexChanged(int index)
{
    int filter_type = ui->comboBox_filterType->currentData().toInt();
    m_op_layout->setCurrentIndex(filter_type);
    m_fiValue_layout->setCurrentIndex(filter_type);
    emit sigModified();
}

// 远程/本地切换
void TasklistCmdEditor::on_groupBox_remote_system_toggled(bool checked)
{
    setupFilterTypes(checked);/*加载过滤器类型列表*/
    m_filter_list.clear();/*清空当前过滤器列表缓存*/
    emit sigModified();
}

void TasklistCmdEditor::on_pushButton_addFilter_clicked()
{
    QString filter_string = QString(" /FI ");

    // 计算过滤条件
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
    case SESSIONNAME:
    {
        fi_type = "SESSIONNAME";
        fi_op = ui->comboBox_op_sessionName->currentData().toString();
        fi_value = ui->lineEdit_fiValue_sessionName->text();
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

void TasklistCmdEditor::on_pushButton_clearFilter_clicked()
{
    m_filter_list.clear();
    emit sigModified();
}

