#include "PingCmdEditor.h"
#include "ui_PingCmdEditor.h"

PingCmdEditor::PingCmdEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PingCmdEditor)
{
    ui->setupUi(this);
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
    QString cmd_string("ping");
    return cmd_string;
}
