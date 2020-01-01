#-------------------------------------------------
#
# Project created by QtCreator 2019-11-04T14:41:15
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LxDairyUpd
TEMPLATE = app
DESTDIR = $$PWD/../LxDairy/bin

SOURCES += main.cpp \
        widget.cpp \
    ../../LxTool/LQtTool/src/LQt.cpp \
    ../../LxTool/LStdTool/src/LStd.cpp \

HEADERS  += widget.h \
    ../../LxTool/LQtTool/src/LQt.h \
    ../../LxTool/LStdTool/src/LStd.h \

FORMS    += widget.ui

INCLUDEPATH += $$PWD/../../LxTool/LQtTool/src
INCLUDEPATH += $$PWD/../../LxTool/LStdTool/src

include($$PWD/../../LxTool/LQtTool/src/network/network.pri)
include($$PWD/../../LxTool/LQtTool/src/core/core.pri)
