#-------------------------------------------------
#
# Project created by QtCreator 2015-08-18T17:28:59
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
QT       += webkitwidgets
QT       += network
QT       += sql

CONFIG   += c++11
CONFIG   += qaxcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = queqiao
TEMPLATE = app

RC_FILE   = queqiao.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    alimamalogin.cpp \
    networkcookie.cpp \
    sqlite.cpp \
    json/json_internalarray.inl \
    json/json_internalmap.inl \
    json/json_reader.cpp \
    json/json_value.cpp \
    json/json_valueiterator.inl \
    json/json_writer.cpp \
    mythread.cpp \
    json_net.cpp \
    itemdetail.cpp \
    aniulogin.cpp \
    sqlitethread.cpp \
    json_netthread.cpp

HEADERS  += mainwindow.h \
    alimamalogin.h \
    networkcookie.h \
    sqlite.h \
    json/autolink.h \
    json/config.h \
    json/features.h \
    json/forwards.h \
    json/json.h \
    json/json_batchallocator.h \
    json/reader.h \
    json/value.h \
    json/writer.h \
    queqiaostruct.h \
    json_net.h \
    mythread.h \
    autoclose.h \
    itemdetail.h \
    aniulogin.h \
    sqlitethread.h \
    json_netthread.h

FORMS    += mainwindow.ui \
    alimamalogin.ui \
    itemdetail.ui \
    aniulogin.ui

DISTFILES += \
    queqiao.rc
