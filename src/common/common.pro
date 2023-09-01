QT += gui widgets

TEMPLATE = lib
CONFIG += dll

DIST_DIR = $$PWD/../../dist
LIB_DEPLOY_DIR = $$PWD/../libs/$$TARGET

CONFIG(debug,debug|release) {
    DESTDIR = $$DIST_DIR/debug
} else {
    DESTDIR = $$DIST_DIR/release
}

DEFINES += COMMONLIB_MAKER

HEADERS += \
    CommonGlobal.h \
    ICmdEditor.h \
    IUnifiedBase.h

SOURCES += \
    ICmdEditor.cpp \
    IUnifiedBase.cpp

# install
headers.files = $$PWD/CommonGlobal.h \
    $$PWD/ICmdEditor.h \
    $$PWD/IUnifiedBase.h
headers.path = $$LIB_DEPLOY_DIR/include

pri.files = common.pri
pri.path = $$LIB_DEPLOY_DIR

CONFIG(debug,debug|release) {
    target.path = $$LIB_DEPLOY_DIR/lib/debug
} else {
    target.path = $$LIB_DEPLOY_DIR/lib/release
}

INSTALLS += headers pri target
