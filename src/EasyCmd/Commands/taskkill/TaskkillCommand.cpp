#include "TaskkillCommand.h"
#include "TaskkillCmdEditor.h"

TaskkillCommand::TaskkillCommand(QObject *parent) : QObject(parent)
{

}

QString TaskkillCommand::getCmdName()
{
    return "taskkill";
}

ICmdEditor *TaskkillCommand::createCmdEditorWidget()
{
    return new TaskkillCmdEditor(this);
}
