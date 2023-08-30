#ifndef COMMANDGLOBAL_H
#define COMMANDGLOBAL_H

#include <QtGlobal>

// 导出宏
#ifdef DLL_MAKER
    #define COMMAND_API Q_DECL_EXPORT
#else
    #define COMMAND_API
#endif

// 属性id
enum PropertyID
{
    PID_CMDNAME, // 命令名称
    PID_CMDEDITOR, // 命令编辑器
    PID_ISMODIFIED, // 是否修改
    PID_CMDSTRING, // 命令字符串
};

enum SignalID
{
    SID_MODIFIED, // 改变消息
};

#endif // COMMANDGLOBAL_H
