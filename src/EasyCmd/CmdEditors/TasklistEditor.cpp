#include "TasklistEditor.h"
#include "ui_TasklistEditor.h"

TasklistEditor::TasklistEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::TasklistEditor)
{
    ui->setupUi(this);
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
    return m_cmd;
}
