#include "DirCommand.h"
#include "DirCmdEditor.h"

DirCommand::DirCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int DirCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "dir";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new DirCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int DirCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}
