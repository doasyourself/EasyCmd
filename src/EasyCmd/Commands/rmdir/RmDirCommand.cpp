#include "RmDirCommand.h"
#include "RmDirCmdEditor.h"

RmDirCommand::RmDirCommand(QObject *parent) : QObject(parent)
{

}

QString RmDirCommand::getCmdName()
{
    return "rmdir";
}

ICmdEditor *RmDirCommand::createCmdEditorWidget()
{
    return new RmDirCmdEditor(this);
}
