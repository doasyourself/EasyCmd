#ifndef COPYCOMMANDGLOBAL_H
#define COPYCOMMANDGLOBAL_H

#ifdef COPYCOMMAND_MAKER
    #define COPYCOMMAND_API Q_DECL_EXPORT
#else
    #define COPYCOMMAND_API Q_DECL_IMPORT
#endif

#endif // COPYCOMMANDGLOBAL_H
