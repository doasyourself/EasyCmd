#include "MkDirCommand.h"
#include "MkDirCmdEditor.h"

MkDirCommand::MkDirCommand(QObject *parent) : QObject(parent)
{

}

QString MkDirCommand::getCmdName()
{
    return "mkdir";
}

ICmdEditor *MkDirCommand::createCmdEditorWidget()
{
    return new MkDirCmdEditor(this);
}
