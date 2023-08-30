#include "PingCommand.h"
#include "PingCmdEditor.h"

PingCommand::PingCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int PingCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "ping";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new PingCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int PingCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}

