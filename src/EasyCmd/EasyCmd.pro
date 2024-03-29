#-------------------------------------------------
#
# Project created by QtCreator 2021-01-24T11:22:21
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyCmd
TEMPLATE = app

DIST_DIR = $$PWD/../../dist
LIBS_DIR = $$PWD/../libs

include($$PWD/Commands/Commands.pri)
include($$PWD/Ui/Ui.pri)
include($$PWD/Utils/Utils.pri)
include($$PWD/Global/Global.pri)
include($$LIBS_DIR/common/common.pri)

CONFIG(debug|release,debug) {
    DESTDIR = $$DIST_DIR/debug
} else {
    DESTDIR = $$DIST_DIR/release
}

win32 {
    QMAKE_CXXFLAGS += /utf-8
    QMAKE_CFLAGS += /utf-8
}

SOURCES += main.cpp

FORMS    +=

TRANSLATIONS += $$PWD/resource/easycmd.ts

RESOURCES += \
    resource/resource.qrc

RC_FILE = $$PWD/resource/rc/app.rc
