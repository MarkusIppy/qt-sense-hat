#-------------------------------------------------
#
# Project created by QtCreator 2016-07-06T07:48:17
#
#-------------------------------------------------

QT       += testlib
QT       += gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += UNIT_TEST

SOURCES += main.cpp \
    ledgridcontrollerut.cpp \
    ../ledgridcontroller.cpp \
    mymock.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ledgridcontrollerut.h \
    ../ledgridcontroller.h \
    mymock.h \
    linux/fb.h
