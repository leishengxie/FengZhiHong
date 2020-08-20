#-------------------------------------------------
#
# Project created by QtCreator 2019-02-25T09:34:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestComplexItemModel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    layertablemodel.cpp \
    layeritemdelegate.cpp \
    layertableview.cpp

HEADERS  += mainwindow.h \
    layertablemodel.h \
    layeritemdelegate.h \
    layertableview.h

FORMS    += mainwindow.ui
