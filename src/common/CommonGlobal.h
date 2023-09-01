#ifndef COMMONGLOBAL_H
#define COMMONGLOBAL_H

#include <QtGlobal>

#ifdef COMMONLIB_MAKER
    #define COMMON_API Q_DECL_EXPORT
#else
    #define COMMON_API Q_DECL_IMPORT
#endif

enum PropertyID
{
    PID_CMDNAME,
    PID_CMDEDITOR,
    PID_CMDSTRING,
};

enum SignalID
{
    SID_MODIFIED,
};

#endif // COMMONGLOBAL_H
