#include "LauncherCommand.h"
#include "LauncherCmdEditor.h"

LauncherCommand::LauncherCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int LauncherCommand::getProperty(int propertyId, QVariant &out_property)
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
        out_property.setValue<void *>(new LauncherCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int LauncherCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}

