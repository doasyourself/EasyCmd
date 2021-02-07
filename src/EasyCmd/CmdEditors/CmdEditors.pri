INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/EditorFactory.h \
    $$PWD/ICmdEditor.h \
    $$PWD/LauncherEditor.h \
    $$PWD/PingCmdEditor.h \
    $$PWD/CmdEditorHeader.h \
    $$PWD/NetStatCmdEditor.h \
    $$PWD/SystemToolEditor.h

SOURCES += \
    $$PWD/EditorFactory.cpp \
    $$PWD/ICmdEditor.cpp \
    $$PWD/LauncherEditor.cpp \
    $$PWD/PingCmdEditor.cpp \
    $$PWD/NetStatCmdEditor.cpp \
    $$PWD/SystemToolEditor.cpp

FORMS += \
    $$PWD/LauncherEditor.ui \
    $$PWD/PingCmdEditor.ui \
    $$PWD/NetStatCmdEditor.ui \
    $$PWD/SystemToolEditor.ui
