#include "CdCommand.h"
#include "CdCmdEditor.h"

CdCommand::CdCommand(QObject *parent) : QObject(parent)
{

}

QString CdCommand::getCmdName()
{
    return "cd";
}

ICmdEditor *CdCommand::createCmdEditorWidget()
{
    return new CdCmdEditor(this);
}
