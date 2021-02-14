#-------------------------------------------------
#
# Project created by QtCreator 2021-01-24T11:22:21
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyCmd
TEMPLATE = app

include($$PWD/CmdEditors/CmdEditors.pri)

CONFIG(debug|release,debug) {
    DESTDIR = $$PWD/dist/debug
} else {
    DESTDIR = $$PWD/dist/release
}

SOURCES += main.cpp\
    CmdProxyModel.cpp \
    CmdTreeModel.cpp \
    ConsoleEditor.cpp \
    ConsoleRwWorker.cpp \
        MainWindow.cpp \
    AboutUsDialog.cpp \
    Utils.cpp \
    ZXmlDomItem.cpp \
    AppTrayIcon.cpp \
    MessageBubble.cpp

HEADERS  += MainWindow.h \
    CmdProxyModel.h \
    AboutUsDialog.h \
    CmdTreeModel.h \
    ConsoleEditor.h \
    ConsoleRwWorker.h \
    Utils.h \
    ZXmlDomItem.h \
    AppTrayIcon.h \
    Global.h \
    MessageBubble.h

FORMS    += MainWindow.ui \
    AboutUsDialog.ui \
    MessageBubble.ui

TRANSLATIONS += $$PWD/resource/easycmd.ts

RESOURCES += \
    resource/resource.qrc

RC_FILE = $$PWD/resource/rc/app.rc
