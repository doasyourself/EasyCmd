INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/CmdEditorHeader.h \
    $$PWD/CommandFactory.h \
    $$PWD/ICmdEditor.h \
    $$PWD/cd/CdCmdEditor.h \
    $$PWD/dir/DirCmdEditor.h \
    $$PWD/ipconfig/IpconfigEditor.h \
    $$PWD/launcher/LauncherEditor.h \
    $$PWD/mkdir/MkDirCmdEditor.h \
    $$PWD/netstat/NetStatCmdEditor.h \
    $$PWD/ping/PingCmdEditor.h \
    $$PWD/rmdir/RmDirCmdEditor.h \
    $$PWD/taskkill/TaskkillEditor.h \
    $$PWD/tasklist/TasklistEditor.h \
    $$PWD/tracert/TracertCmdEditor.h \
    $$PWD/windows-systemtool/SystemToolEditor.h

SOURCES += \
    $$PWD/CommandFactory.cpp \
    $$PWD/ICmdEditor.cpp \
    $$PWD/cd/CdCmdEditor.cpp \
    $$PWD/dir/DirCmdEditor.cpp \
    $$PWD/ipconfig/IpconfigEditor.cpp \
    $$PWD/launcher/LauncherEditor.cpp \
    $$PWD/mkdir/MkDirCmdEditor.cpp \
    $$PWD/netstat/NetStatCmdEditor.cpp \
    $$PWD/ping/PingCmdEditor.cpp \
    $$PWD/rmdir/RmDirCmdEditor.cpp \
    $$PWD/taskkill/TaskkillEditor.cpp \
    $$PWD/tasklist/TasklistEditor.cpp \
    $$PWD/tracert/TracertCmdEditor.cpp \
    $$PWD/windows-systemtool/SystemToolEditor.cpp

FORMS += \
    $$PWD/cd/CdCmdEditor.ui \
    $$PWD/dir/DirCmdEditor.ui \
    $$PWD/ipconfig/IpconfigEditor.ui \
    $$PWD/launcher/LauncherEditor.ui \
    $$PWD/mkdir/MkDirCmdEditor.ui \
    $$PWD/netstat/NetStatCmdEditor.ui \
    $$PWD/ping/PingCmdEditor.ui \
    $$PWD/rmdir/RmDirCmdEditor.ui \
    $$PWD/taskkill/TaskkillEditor.ui \
    $$PWD/tasklist/TasklistEditor.ui \
    $$PWD/tracert/TracertCmdEditor.ui \
    $$PWD/windows-systemtool/SystemToolEditor.ui
