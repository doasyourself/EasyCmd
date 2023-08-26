#include "NetStatCommand.h"
#include "NetStatCmdEditor.h"

NetStatCommand::NetStatCommand(QObject *parent) : QObject(parent)
{

}

QString NetStatCommand::getCmdName()
{
    return "netstat";
}

ICmdEditor *NetStatCommand::createCmdEditorWidget()
{
    return new NetStatCmdEditor(this);
}
