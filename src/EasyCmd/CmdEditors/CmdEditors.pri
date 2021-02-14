INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/EditorFactory.h \
    $$PWD/ICmdEditor.h \
    $$PWD/LauncherEditor.h \
    $$PWD/PingCmdEditor.h \
    $$PWD/CmdEditorHeader.h \
    $$PWD/NetStatCmdEditor.h \
    $$PWD/SystemToolEditor.h \
    $$PWD/IpconfigEditor.h \
    $$PWD/TasklistEditor.h \
    $$PWD/TaskkillEditor.h

SOURCES += \
    $$PWD/EditorFactory.cpp \
    $$PWD/ICmdEditor.cpp \
    $$PWD/LauncherEditor.cpp \
    $$PWD/PingCmdEditor.cpp \
    $$PWD/NetStatCmdEditor.cpp \
    $$PWD/SystemToolEditor.cpp \
    $$PWD/IpconfigEditor.cpp \
    $$PWD/TasklistEditor.cpp \
    $$PWD/TaskkillEditor.cpp

FORMS += \
    $$PWD/LauncherEditor.ui \
    $$PWD/PingCmdEditor.ui \
    $$PWD/NetStatCmdEditor.ui \
    $$PWD/SystemToolEditor.ui \
    $$PWD/IpconfigEditor.ui \
    $$PWD/TasklistEditor.ui \
    $$PWD/TaskkillEditor.ui
