#include "CommandFactory.h"
#include "ping/PingCommand.h"
#include "netstat/NetStatCommand.h"
#include "win-systemtool/WinSystemToolCmdEditor.h"
#include "launcher/LauncherCommand.h"
#include "ipconfig/IPConfigCommand.h"
#include "tasklist/TasklistCommand.h"
#include "taskkill/TaskkillCommand.h"
#include "tracert/TracertCommand.h"
#include "copy/CopyCommand.h"
#include "cd/CdCommand.h"
#include "mkdir/MkDirCommand.h"
#include "rmdir/RmDirCommand.h"
#include "dir/DirCommand.h"

ICommand *newPingCommand() { return new PingCommand; }
ICommand *newNetStatCommand() { return new NetStatCommand; }
ICommand *newWinSystemToolCommand() { return new WinSystemToolCommand; }
ICommand *newLauncherCommand() { return new LauncherCommand; }
ICommand *newIPConfigCommand() { return new IPConfigCommand; }
ICommand *newTasklistCommand() { return new TasklistCommand; }
ICommand *newTaskkillCommand() { return new TaskkillCommand; }
ICommand *newTracertCommand() { return new TracertCommand; }
ICommand *newCdCommand() { return new CdCommand; }
ICommand *newDirCommand() { return new DirCommand; }
ICommand *newMkDirCommand() { return new MkDirCommand; }
ICommand *newRmDirCommand() { return new RmDirCommand; }
ICommand *newCopyCommand() { return new CopyCommand; }

CommandFactory::CommandFactory()
{
    m_editor_map.clear();

    // 关键字小写
    // 注册/保存所有创建接口
    m_editor_map.insert("ping", newPingCommand);
    m_editor_map.insert("netstat", newNetStatCommand);
    m_editor_map.insert("systemTools", newWinSystemToolCommand);
    m_editor_map.insert("launcher", newLauncherCommand);
    m_editor_map.insert("ipconfig", newIPConfigCommand);
    m_editor_map.insert("tasklist", newTasklistCommand);
    m_editor_map.insert("taskkill", newTaskkillCommand);
    m_editor_map.insert("tracert", newTracertCommand);
    m_editor_map.insert("cd", newCdCommand);
    m_editor_map.insert("dir", newDirCommand);
    m_editor_map.insert("mkdir", newMkDirCommand);
    m_editor_map.insert("rmdir", newRmDirCommand);
    m_editor_map.insert("copy", newCopyCommand);
}

ICommand *CommandFactory::createCommand(const QString &command_id)
{
    ICommand *command = NULL;
    newEditorFunc func = m_editor_map.value(command_id);
    if (func) command = func();
    return command;
}
