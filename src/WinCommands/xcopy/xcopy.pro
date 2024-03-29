QT += widgets

TEMPLATE = lib
DEFINES += DLL_MAKER

CONFIG += c++11
DESTDIR = $$PWD/dist

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/../common/common.pri)

SOURCES += \
    XCopyCmdEditor.cpp \
    XCopyCommand.cpp

HEADERS += \
    XCopyCmdEditor.h \
    XCopyCommand.h

win32:{
    QMAKE_CXXFLAGS += /utf-8
    QMAKE_CFLAGS += /utf-8
}

# install
win32: {
    target.files = $$DESTDIR/$$join(TARGET,,,".dll")
}

CONFIG(debug,debug|release) {
    target.path = $$PWD/../../dist/debug/plugins/$$TARGET
} else {
    target.path = $$PWD/../../dist/release/plugins/$$TARGET
}
INSTALLS += target

FORMS += \
    XCopyCmdEditor.ui
