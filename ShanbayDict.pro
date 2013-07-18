TEMPLATE = app
TARGET = ShanbayDict
QT += core gui network webkit multimedia testlib
#phonon
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

CONFIG += C++11
win32:RC_FILE = app.rc
win32 {
    INCLUDEPATH +=./lib
    Release:LIBS  += -L../ShanbayDict/lib  -lWinHook
    Debug:LIBS  += -L../ShanbayDict/lib/debug  -lWinHook
}

CONFIG(debug, debug|release) {
    MOC_DIR = $$OUT_PWD/tmp/debug
    UI_DIR = $$OUT_PWD/tmp/debug
    RCC_DIR = $$OUT_PWD/tmp/debug
    OBJECTS_DIR = $$OUT_PWD/tmp/debug
    DEFINES += DEBUG
}else{
    MOC_DIR = $$OUT_PWD/tmp/release
    UI_DIR = $$OUT_PWD/tmp/release
    RCC_DIR = $$OUT_PWD/tmp/release
    OBJECTS_DIR = $$OUT_PWD/tmp/release
    DEFINES += NDEBUG
}
#DEFINES += QT_NO_WARNING_OUTPUT\
#           QT_NO_DEBUG_OUTPUT


INCLUDEPATH += src
SOURCES += \
    src/main.cpp \
    src/shanbaynet.cpp \
    src/logindialog.cpp \
    src/englishword.cpp \
    src/mainwindow.cpp \
    src/clicklabel.cpp \
    src/ballonwindow.cpp \
    src/dict.cpp \
    src/config.cpp \
    src/picturebutton.cpp \
    src/history.cpp \
    src/dictview.cpp \
    src/texttranslatenet.cpp \
    src/cfgdialog.cpp
HEADERS  += \
    src/shanbaynet.h \
    src/logindialog.h \
    src/englishword.h \
    src/mainwindow.h \
    src/clicklabel.h \
    src/ballonwindow.h \
    src/dict.h \
    src/config.h \
    src/picturebutton.h \
    src/history.h \
    src/dictview.h \
    src/texttranslatenet.h \
    src/cfgdialog.h
FORMS    += \
    src/logindialog.ui \
    src/mainwindow.ui \
    src/ballonwindow.ui \
    src/dictview.ui \
    src/cfgdialog.ui
RESOURCES += \
    icons.qrc

