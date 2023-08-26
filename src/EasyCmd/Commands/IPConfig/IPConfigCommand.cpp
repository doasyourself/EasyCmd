#include "IPConfigCommand.h"
#include "IPConfigCmdEditor.h"

IPConfigCommand::IPConfigCommand(QObject *parent) : QObject(parent)
{

}

QString IPConfigCommand::getCmdName()
{
    return "ipconfig";
}

ICmdEditor *IPConfigCommand::createCmdEditorWidget()
{
    return new IPConfigCmdEditor(this);
}
