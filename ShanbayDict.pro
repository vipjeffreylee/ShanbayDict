#-------------------------------------------------
#
# Project created by QtCreator 2012-01-06T14:00:30
#
#-------------------------------------------------

QT       += core gui\
            network\
            webkitwidgets\
            multimedia
            #phonon
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = ShanbayDict
TEMPLATE = app

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
    src/cfgdialog.cpp \
    src/youdaonet.cpp
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
    src/cfgdialog.h \
    src/youdaonet.h
FORMS    += \
    src/logindialog.ui \
    src/mainwindow.ui \
    src/ballonwindow.ui \
    src/dictview.ui \
    src/cfgdialog.ui
win32{
    INCLUDEPATH +=./lib
    Release:LIBS  += -L../ShanbayDict/lib  -lWinHook
    Debug:LIBS  += -L../ShanbayDict/lib/debug  -lWinHook
}
CONFIG += C++11
RESOURCES += \
    icons.qrc
RC_FILE = app.rc
macx{
ICON = logo.icns
}

CONFIG(debug, debug|release) {
    DEFINES += DEBUG
}else{
    DEFINES += NDEBUG
}
#DEFINES += QT_NO_WARNING_OUTPUT\
#           QT_NO_DEBUG_OUTPUT




































