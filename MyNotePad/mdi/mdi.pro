#-------------------------------------------------
#
# Project created by QtCreator 2012-09-01T08:51:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mymdi.cpp

HEADERS  += mainwindow.h \
    mymdi.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
