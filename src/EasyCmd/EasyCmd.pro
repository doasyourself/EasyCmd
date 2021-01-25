#-------------------------------------------------
#
# Project created by QtCreator 2021-01-24T11:22:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyCmd
TEMPLATE = app

include($$PWD/CmdEditors/CmdEditors.pri)

DESTDIR = $$PWD/dist

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui
