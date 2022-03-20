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
include($$PWD/Ui/Ui.pri)

CONFIG(debug|release,debug) {
    DESTDIR = $$PWD/../dist/debug
} else {
    DESTDIR = $$PWD/../dist/release
}

SOURCES += main.cpp\
    Utils.cpp

HEADERS  += Utils.h \
    Global.h \
    Utils.h

FORMS    +=

TRANSLATIONS += $$PWD/resource/easycmd.ts

RESOURCES += \
    resource/resource.qrc

RC_FILE = $$PWD/resource/rc/app.rc
