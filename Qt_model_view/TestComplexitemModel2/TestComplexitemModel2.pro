#-------------------------------------------------
#
# Project created by QtCreator 2019-02-25T10:59:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestComplexitemModel2
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    delegate.cpp \
    inputagedlg.cpp

HEADERS  += mainwindow.h \
    delegate.h \
    inputagedlg.h

FORMS    += mainwindow.ui \
    inputagedlg.ui
