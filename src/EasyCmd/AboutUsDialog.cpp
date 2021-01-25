#include "AboutUsDialog.h"
#include "ui_AboutUsDialog.h"
#include "Utils.h"

AboutUsDialog::AboutUsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutUsDialog)
{
    ui->setupUi(this);

    ui->label_version->setText(qApp->applicationVersion());
    ui->label_compileTime->setText(QString::number(Utils::getCompileDateTime().date().year()));
}

AboutUsDialog::~AboutUsDialog()
{
    delete ui;
}
