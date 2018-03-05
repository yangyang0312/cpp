#-------------------------------------------------
#
# Project created by QtCreator 2017-11-26T15:13:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

SOURCES += main.cpp

#包含路径
INCLUDEPATH +=  $$PWD/../testdll
#输出路径
CONFIG += debug_and_release
CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../Debug
}else{
    DESTDIR = $$PWD/../Release
}
#链接lib
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Release -ltestdll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Debug/ -ltestdll
