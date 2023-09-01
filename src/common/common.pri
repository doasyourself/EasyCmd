INCLUDEPATH += $$PWD/include

CONFIG(debug,debug|release) {
    LIBS += -L$$PWD/lib/debug -lcommon
} else {
    LIBS += -L$$PWD/lib/release -lcommon
}
