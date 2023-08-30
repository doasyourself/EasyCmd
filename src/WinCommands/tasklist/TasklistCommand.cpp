#include "TasklistCommand.h"
#include "TasklistCmdEditor.h"

TasklistCommand::TasklistCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int TasklistCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "tasklist";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new TasklistCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int TasklistCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}

