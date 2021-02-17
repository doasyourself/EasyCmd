/*******************************************************************************
** FI：Filter
** FO: Format
********************************************************************************/

#include "TasklistEditor.h"
#include "ui_TasklistEditor.h"
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

TasklistEditor::TasklistEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::TasklistEditor)
{
    ui->setupUi(this);

    on_checkBox_remote_system_toggled(false);
    on_checkBox_option_m_toggled(false);
    on_checkBox_option_fo_toggled(false);
    on_checkBox_option_fi_toggled(false);
    on_comboBox_option_fo_currentIndexChanged(ui->comboBox_option_fo->currentText());

    // 初始化隐藏错误信息提示
    ui->label_info_option_s->hide();

    // 初始化过滤器
    initFilters();
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
    QString cmd = getCmdName();
    QString options;

    do
    {
        // /S选项
        if (ui->checkBox_remote_system->isChecked())
        {
            options += " /S";

            QString hostname = ui->lineEdit_option_s->text();
            if (hostname.isEmpty()) // error
            {
                Utils::showTip(ui->label_info_option_s, tr("Hostname can't be empty!"));
                break;
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
        if (ui->checkBox_option_fi->isChecked())
        {
            options += QString(" /FI ");

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
                fi_op = ui->comboBox_op_status->currentText();
                fi_value = ui->comboBox_fiValue_status->currentText();
                break;
            }
            case IMAGENAME:
            {
                fi_type = "IMAGENAME";
                fi_op = ui->comboBox_op_imageName->currentText();
                fi_value = ui->lineEdit_fiValue_imageName->text();
                break;
            }
            case PID:
            {
                fi_type = "IMAGENAME";
                fi_op = ui->comboBox_op_pid->currentText();
                fi_value = ui->lineEdit_fiValue_pid->text();
                break;
            }
            case SESSION:
            {
                fi_type = "SESSION";
                fi_op = ui->comboBox_op_session->currentText();
                fi_value = ui->lineEdit_fiValue_session->text();
                break;
            }
            case SESSIONNAME:
            {
                fi_type = "SESSIONNAME";
                fi_op = ui->comboBox_op_sessionName->currentText();
                fi_value = ui->lineEdit_fiValue_sessionName->text();
                break;
            }
            case CPUTIME:
            {
                fi_type = "CPUTIME";
                fi_op = ui->comboBox_op_cpuTime->currentText();
                fi_value = ui->timeEdit_fiValue_cpuTime->text();
                break;
            }
            case MEMUSAGE:
            {
                fi_type = "MEMUSAGE";
                fi_op = ui->comboBox_op_memusage->currentText();
                fi_value = ui->spinBox_fiValue_memUsage->text();
                break;
            }
            case USERNAME:
            {
                fi_type = "USERNAME";
                fi_op = ui->comboBox_op_userName->currentText();
                fi_value = ui->lineEdit_fiValue_userName->text();
                break;
            }
            case SERVICES:
            {
                fi_type = "SERVICES";
                fi_op = ui->comboBox_op_service->currentText();
                fi_value = ui->lineEdit_fiValue_service->text();
                break;
            }
            case WINDOWTITLE:
            {
                fi_type = "WINDOWTITLE";
                fi_op = ui->comboBox_op_windowTitle->currentText();
                fi_value = ui->lineEdit_fiValue_windowTitle->text();
                break;
            }
            case MODULES:
            {
                fi_type = "MODULES";
                fi_op = ui->comboBox_op_module->currentText();
                fi_value = ui->lineEdit_fiValue_module->text();
                break;
            }
            default:
            {
                Q_ASSERT(0);
                break;
            }
            }

            options += QString("\"%1 %2 %3\"").arg(fi_type).arg(fi_op).arg(fi_value);
        }

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

void TasklistEditor::on_checkBox_remote_system_toggled(bool checked)
{
    ui->groupBox_remote_system->setEnabled(checked);
    emit sigModified();
}

void TasklistEditor::on_checkBox_option_m_toggled(bool checked)
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
void TasklistEditor::on_checkBox_option_v_toggled(bool checked)
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
void TasklistEditor::on_checkBox_option_svc_toggled(bool checked)
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
void TasklistEditor::on_comboBox_option_fo_currentIndexChanged(const QString &txt)
{
    // 更新/NH选项状态
    bool is_nh_enable = ui->checkBox_option_fo->isChecked() && (txt == "TABLE" || txt == "CSV");
    ui->checkBox_option_nh->setEnabled(is_nh_enable);
    emit sigModified();
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
    ui->groupBox_filter->setEnabled(checked);
    emit sigModified();
}

// 主机名编辑框
void TasklistEditor::on_lineEdit_option_s_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// 用户名编辑框
void TasklistEditor::on_lineEdit_option_u_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// 密码编辑框
void TasklistEditor::on_lineEdit_option_p_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// 运行模块筛选
void TasklistEditor::on_lineEdit_option_m_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    emit sigModified();
}

// 无表头选项
void TasklistEditor::on_checkBox_option_nh_toggled(bool checked)
{
    Q_UNUSED(checked);
    emit sigModified();
}

void TasklistEditor::initFilters()
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
    connect(ui->comboBox_op_status, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_imageName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_pid, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_session, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_sessionName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_cpuTime, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_memusage, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_userName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_service, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_windowTitle, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->comboBox_op_module, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);

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
    connect(ui->comboBox_fiValue_status, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &TasklistEditor::sigModified);
    connect(ui->lineEdit_fiValue_imageName, &QLineEdit::textChanged, this, &TasklistEditor::sigModified);
    connect(ui->lineEdit_fiValue_pid, &QLineEdit::textChanged, this, &TasklistEditor::sigModified);
    connect(ui->lineEdit_fiValue_session, &QLineEdit::textChanged, this, &TasklistEditor::sigModified);
    connect(ui->lineEdit_fiValue_sessionName, &QLineEdit::textChanged, this, &TasklistEditor::sigModified);
    connect(ui->timeEdit_fiValue_cpuTime, &QTimeEdit::timeChanged, this, &TasklistEditor::sigModified);
    connect(ui->spinBox_fiValue_memUsage, QOverload<int>::of(&QSpinBox::valueChanged), this, &TasklistEditor::sigModified);
    connect(ui->lineEdit_fiValue_userName, &QLineEdit::textChanged, this, &TasklistEditor::sigModified);
    connect(ui->lineEdit_fiValue_service, &QLineEdit::textChanged, this, &TasklistEditor::sigModified);
    connect(ui->lineEdit_fiValue_windowTitle, &QLineEdit::textChanged, this, &TasklistEditor::sigModified);
    connect(ui->lineEdit_fiValue_module, &QLineEdit::textChanged, this, &TasklistEditor::sigModified);

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

    // 最后再添加过滤类型，因为会发出切换信号，其他都准备好再切换
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

void TasklistEditor::on_comboBox_filterType_currentIndexChanged(int index)
{
    m_op_layout->setCurrentIndex(index);
    m_fiValue_layout->setCurrentIndex(index);
    emit sigModified();
}
