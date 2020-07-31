#-------------------------------------------------
#
# Project created by QtCreator 2020-07-23T21:27:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LxDailySchedule
TEMPLATE = app


SOURCES += main.cpp\
    DailyScheduleBookListView.cpp \
    DailyScheduleBookModel.cpp \
    DailyScheduleModel.cpp \
    DailyScheduleDelegate.cpp \
    DailyScheduleTableView.cpp \
    StartEndTimeEditor.cpp \
    DailyScheduleWidget.cpp

HEADERS  += \
    DailyScheduleBookListView.h \
    DailyScheduleBookModel.h \
    DailyScheduleModel.h \
    DailyScheduleDelegate.h \
    DailyScheduleTableView.h \
    StartEndTimeEditor.h \
    DailyScheduleWidget.h

FORMS    += \
    DailyScheduleWidget.ui

RESOURCES += \
    res.qrc
