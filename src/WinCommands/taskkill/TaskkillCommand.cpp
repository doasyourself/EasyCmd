#include "TaskkillCommand.h"
#include "TaskkillCmdEditor.h"

TaskkillCommand::TaskkillCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int TaskkillCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "taskkill";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new TaskkillCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int TaskkillCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}

