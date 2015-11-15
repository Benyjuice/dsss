#-------------------------------------------------
#
# Project created by QtCreator 2015-11-15T15:03:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS''= -lfftw3

TARGET = dsss-receiver
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dsss-core.c \
    process_line.c \
    dsss-global.c

HEADERS  += mainwindow.h \
    common.h \
    dsss-global.h

FORMS    += mainwindow.ui

DISTFILES += \
    dsss-receiver.pro.user
