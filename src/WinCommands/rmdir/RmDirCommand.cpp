#include "RmDirCommand.h"
#include "RmDirCmdEditor.h"

RmDirCommand::RmDirCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int RmDirCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "rmdir";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new RmDirCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int RmDirCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}

