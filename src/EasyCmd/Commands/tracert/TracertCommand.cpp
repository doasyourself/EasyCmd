#include "TracertCommand.h"
#include "TracertCmdEditor.h"

TracertCommand::TracertCommand(QObject *parent) : QObject(parent)
{

}

QString TracertCommand::getCmdName()
{
    return "tracert";
}

ICmdEditor *TracertCommand::createCmdEditorWidget()
{
    return new TracertCmdEditor(this);
}
