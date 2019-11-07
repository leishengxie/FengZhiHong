#-------------------------------------------------
#
# Project created by QtCreator 2017-07-29T15:55:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChangeEncoding
TEMPLATE = app

DESTDIR = $$PWD/bin


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RC_FILE += icon.rc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LxTool/LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LxTool/LQtTool/bin/ -lLQtToold

INCLUDEPATH += $$PWD/../LxTool/LQtTool/include
DEPENDPATH += $$PWD/../LxTool/LQtTool/include
