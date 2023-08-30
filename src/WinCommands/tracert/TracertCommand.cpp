#include "TracertCommand.h"
#include "TracertCmdEditor.h"

TracertCommand::TracertCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int TracertCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "tracert";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new TracertCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int TracertCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}
