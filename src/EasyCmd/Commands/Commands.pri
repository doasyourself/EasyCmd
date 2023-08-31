INCLUDEPATH += $$PWD $$PWD/../../WinCommands/common

HEADERS += \
    $$PWD/../../WinCommands/common/CommandGlobal.h \
    $$PWD/../../WinCommands/common/ICmdEditor.h \
    $$PWD/../../WinCommands/common/IUnifiedBase.h \
    $$PWD/CommandFactory.h

SOURCES += \
    $$PWD/../../WinCommands/common/IUnifiedBase.cpp \
    $$PWD/CommandFactory.cpp
