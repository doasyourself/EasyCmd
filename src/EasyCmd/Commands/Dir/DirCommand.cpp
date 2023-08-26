#include "DirCommand.h"
#include "DirCmdEditor.h"

DirCommand::DirCommand(QObject *parent) : QObject(parent)
{

}

QString DirCommand::getCmdName()
{
    return "dir";
}

ICmdEditor *DirCommand::createCmdEditorWidget()
{
    return new DirCmdEditor(this);
}
