#include "TracertCmdEditor.h"
#include "ui_TracertCmdEditor.h"

TracertCmdEditor::TracertCmdEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::TracertCmdEditor)
{
    ui->setupUi(this);
}

TracertCmdEditor::~TracertCmdEditor()
{
    delete ui;
}

bool TracertCmdEditor::isModified() const
{
    return true;
}

QString TracertCmdEditor::getCmdName()
{
    return "tracert";
}

QString TracertCmdEditor::getCmdString()
{
    return "";
}
