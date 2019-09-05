#-------------------------------------------------
#
# Project created by QtCreator 2019-08-25T14:52:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LxDairy
TEMPLATE = app


SOURCES += main.cpp\
    LoginWidget.cpp \
    AboutDialog.cpp \
    DairyMainWindow.cpp \
    SqlOperate.cpp

HEADERS  += \
    LoginWidget.h \
    AboutDialog.h \
    DairyMainWindow.h \
    SqlOperate.h

FORMS    += \
    LoginWidget.ui \
    DairyMainWindow.ui \
    AboutDialog.ui

RESOURCES += \
    res.qrc
