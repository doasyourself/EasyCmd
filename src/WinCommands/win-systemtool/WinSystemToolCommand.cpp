#include "WinSystemToolCommand.h"
#include "WinSystemToolCmdEditor.h"

WinSystemToolCommand::WinSystemToolCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int WinSystemToolCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new WinSystemToolCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int WinSystemToolCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}
