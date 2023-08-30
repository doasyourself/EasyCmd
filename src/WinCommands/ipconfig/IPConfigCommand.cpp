#include "IPConfigCommand.h"
#include "IPConfigCmdEditor.h"

IPConfigCommand::IPConfigCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int IPConfigCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "ipconfig";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new IPConfigCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int IPConfigCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}
