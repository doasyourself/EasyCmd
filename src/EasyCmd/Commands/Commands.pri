INCLUDEPATH += $$PWD

DEFINES += DLL_MAKER

HEADERS += \
    $$PWD/CommandFactory.h \
    $$PWD/CommandGlobal.h \
    $$PWD/ICmdEditor.h \
    $$PWD/IUnifiedBase.h

SOURCES += \
    $$PWD/CommandFactory.cpp \
    $$PWD/ICmdEditor.cpp \
    $$PWD/IUnifiedBase.cpp
