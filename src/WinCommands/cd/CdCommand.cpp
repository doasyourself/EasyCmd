#include "CdCommand.h"
#include "CdCmdEditor.h"
#include "CdCmdEditor.h"

CdCommand::CdCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int CdCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "cd";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new CdCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int CdCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}
