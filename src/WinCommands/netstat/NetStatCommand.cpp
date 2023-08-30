#include "NetStatCommand.h"
#include "NetStatCmdEditor.h"

NetStatCommand::NetStatCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int NetStatCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "netstat";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new NetStatCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int NetStatCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}
