#include "MkDirCommand.h"
#include "MkDirCmdEditor.h"

MkDirCommand::MkDirCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int MkDirCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "mkdir";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new MkDirCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int MkDirCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}

