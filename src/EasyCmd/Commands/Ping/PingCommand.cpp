#include "PingCommand.h"
#include "PingCmdEditor.h"

PingCommand::PingCommand(QObject *parent) : QObject(parent)
{

}

QString PingCommand::getCmdName()
{
    return "ping";
}

ICmdEditor *PingCommand::createCmdEditorWidget()
{
    return new PingCmdEditor(this);
}
