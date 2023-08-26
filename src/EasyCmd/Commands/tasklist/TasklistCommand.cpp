#include "TasklistCommand.h"
#include "TasklistCmdEditor.h"

TasklistCommand::TasklistCommand(QObject *parent) : QObject(parent)
{

}

QString TasklistCommand::getCmdName()
{
    return "tasklist";
}

ICmdEditor *TasklistCommand::createCmdEditorWidget()
{
    return new TasklistCmdEditor(this);
}
