#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T16:39:32
#
#-------------------------------------------------

QT       += widgets

TARGET = testQt
TEMPLATE = lib

DEFINES += TESTQT_LIBRARY

SOURCES += \
    main.cpp \
    qmfcapp.cpp \
    qwinwidget.cpp \
    dialog.cpp

HEADERS += \
    qmfcapp.h \
    qwinwidget.h \
    dialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
#编译路径
CONFIG += debug_and_release
CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../Debug
}else{
    DESTDIR = $$PWD/../Release
}

FORMS += \
    dialog.ui
