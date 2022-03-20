#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include "Utils.h"

AboutDialog::AboutDialog(QWidget *parent) :
    MyDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    init();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::init()
{
    setWindowTitle(tr("About %1").arg(qApp->applicationName()));

    connect(ui->pushButton_close, &QPushButton::clicked, this, &AboutDialog::accept);

    // 版本日期信息
    ui->label_version->setText(qApp->applicationName());
    ui->label_build_time->setText(tr("Build on %1").arg(Utils::getCompileDateTime().toString("yyyy/MM/dd hh:mm:ss")));
}
