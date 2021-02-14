#include "TaskkillEditor.h"
#include "ui_TaskkillEditor.h"

TaskkillEditor::TaskkillEditor(QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::TaskkillEditor)
{
    ui->setupUi(this);
}

TaskkillEditor::~TaskkillEditor()
{
    delete ui;
}

bool TaskkillEditor::isModified() const
{
    return false;
}

QString TaskkillEditor::getCmdName()
{
    return "taskkill";
}

QString TaskkillEditor::getCmdString()
{
    return m_cmd;
}
