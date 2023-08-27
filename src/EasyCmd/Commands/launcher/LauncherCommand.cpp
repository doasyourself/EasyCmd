#include "LauncherCommand.h"
#include "LauncherCmdEditor.h"

LauncherCommand::LauncherCommand(QObject *parent) : QObject(parent)
{

}

QString LauncherCommand::getCmdName()
{
    return "";
}

ICmdEditor *LauncherCommand::createCmdEditorWidget()
{
    return new LauncherCmdEditor(this);
}
