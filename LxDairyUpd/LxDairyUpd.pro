#-------------------------------------------------
#
# Project created by QtCreator 2019-11-04T14:41:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LxDairyUpd
TEMPLATE = app
DESTDIR = $$PWD/../LxDairy/bin

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui


#链接#
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
else:unix: LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool


#依赖头文#
INCLUDEPATH += $$PWD/../../LxTool/LQtTool/include
DEPENDPATH += $$PWD/../../LxTool/LQtTool/include
