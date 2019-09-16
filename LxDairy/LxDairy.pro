#-------------------------------------------------
#
# Project created by QtCreator 2019-08-25T14:52:35
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LxDairy
TEMPLATE = app


SOURCES += main.cpp\
    LoginWidget.cpp \
    AboutDialog.cpp \
    DairyMainWindow.cpp \
    SqlOperate.cpp \
    GlobalFunc.cpp \
    AwesomeFont.cpp \
    SkinWidget.cpp \
    RegisterDialog.cpp \
    TextVerifier.cpp \
    model/DairyTagListModel.cpp \
    delegate/DairyTagDelegate.cpp \
    model/DairyDateTreeModel.cpp

HEADERS  += \
    LoginWidget.h \
    AboutDialog.h \
    DairyMainWindow.h \
    SqlOperate.h \
    GlobalFunc.h \
    AwesomeFont.h \
    SkinWidget.h \
    RegisterDialog.h \
    TextVerifier.h \
    model/DairyTagListModel.h \
    delegate/DairyTagDelegate.h \
    model/DairyDateTreeModel.h

FORMS    += \
    LoginWidget.ui \
    DairyMainWindow.ui \
    AboutDialog.ui \
    SkinWidget.ui \
    RegisterDialog.ui

RESOURCES += \
    res.qrc
