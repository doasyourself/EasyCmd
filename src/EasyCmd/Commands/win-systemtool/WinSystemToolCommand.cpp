#include "WinSystemToolCommand.h"
#include "WinSystemToolCmdEditor.h"

WinSystemToolCommand::WinSystemToolCommand(QObject *parent) : QObject(parent)
{

}

QString WinSystemToolCommand::getCmdName()
{
    return "";
}

ICmdEditor *WinSystemToolCommand::createCmdEditorWidget()
{
    return new WinSystemToolCmdEditor(this);
}
