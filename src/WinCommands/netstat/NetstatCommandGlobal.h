#ifndef NETSTATCOMMANDGLOBAL_H
#define NETSTATCOMMANDGLOBAL_H

#ifdef NETSTATCOMMAND_MAKER
    #define NETSTATCOMMAND_API Q_DECL_EXPORT
#else
    #define NETSTATCOMMAND_API Q_DECL_IMPORT
#endif

#endif // NETSTATCOMMANDGLOBAL_H
