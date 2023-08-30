#include "CopyCommand.h"
#include "CopyCmdEditor.h"

CopyCommand::CopyCommand(QObject *parent) : IUnifiedBase(parent)
{

}

int CopyCommand::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDNAME:
    {
        out_property = "copy";
        break;
    }
    case PID_CMDEDITOR:
    {
        out_property.setValue<void *>(new CopyCmdEditor(this));
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int CopyCommand::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}

