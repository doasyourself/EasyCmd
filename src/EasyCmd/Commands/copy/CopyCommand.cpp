#include "CopyCommand.h"
#include "CopyCmdEditor.h"

CopyCommand::CopyCommand(QObject *parent) : QObject(parent)
{

}

QString CopyCommand::getCmdName()
{
    return "copy";
}

ICmdEditor *CopyCommand::createCmdEditorWidget()
{
    return new CopyCmdEditor(this);
}
