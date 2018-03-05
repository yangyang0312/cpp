#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T15:19:25
#
#-------------------------------------------------

QT       += widgets

TARGET = testDll
TEMPLATE = lib

DEFINES += TESTDLL_LIBRARY

SOURCES += \
    dialog.cpp

HEADERS +=\
        testdll_global.h \
    dialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    dialog.ui
#编译路径
CONFIG += debug_and_release
CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../Debug
}else{
    DESTDIR = $$PWD/../Release
}
