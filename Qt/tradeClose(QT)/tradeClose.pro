#-------------------------------------------------
#
# Project created by QtCreator 2015-08-08T15:38:50
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
QT       += webkitwidgets
QT       += network

CONFIG   += c++11

//图标
RC_FILE   = tradeClose.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tradeClose
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    networkcookie.cpp

HEADERS  += mainwindow.h \
    login.h \
    networkcookie.h

FORMS    += mainwindow.ui \
    login.ui

DISTFILES += \
    tradeClose.rc
