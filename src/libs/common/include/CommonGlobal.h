#ifndef COMMONGLOBAL_H
#define COMMONGLOBAL_H

#include <QtGlobal>

#ifdef COMMONLIB_MAKER
    #define COMMON_API Q_DECL_EXPORT
#else
    #define COMMON_API Q_DECL_IMPORT
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

#endif // COMMONGLOBAL_H
